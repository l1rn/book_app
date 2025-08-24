#include <sqlite3.h>
#include <stdio.h>

#include "author_dao.h"

#include <stdlib.h>

int author_dao_check_existence(sqlite3 *db, const unsigned char *name, const unsigned char *surname);

void handle_dao_sql_error(dao_status status) {
	const char *msg = NULL;
	switch (status) {
		case DAO_ERROR_PREPARE:
			msg = "SQL prepare failed.";
			break;
		case DAO_ERROR_EXECUTE:
			msg = "SQL execution failed.";
			break;
		case DAO_ERROR_BIND:
			msg = "SQL bind failed.";
			break;
		case DAO_ERROR_NOT_FOUND:
			msg  = "Record not found.";
			break;
		case DAO_ERROR_UNKNOWN:
			msg = "Unable to allocate memory";
			break;
		case DAO_ALREADY_EXIST:
			msg = "Record already exist";
			break;
		default:
			msg = "Unknown error.";
			break;
	}

	fprintf(stderr, "%s %s\n", msg);
}

// Create
dao_status author_dao_create(DAOContext *ctx, const char* name, const char* surname, int64_t *out_new_id){
	if (ctx == NULL || out_new_id == NULL) {
		return DAO_ERROR_INVALID_ARGS;
	}

	sqlite3 *db = db_get_handle(ctx);
	if (!db | !name | !surname) {
		return DAO_ERROR_INVALID_ARGS;
	}

	if (author_dao_check_existence(db, (const unsigned char *) name, (const unsigned char *) surname) == 1) {
		return DAO_ALREADY_EXIST;
	}
	sqlite3_stmt *stmt = NULL;
	const char *sql = "INSERT INTO Author (name, surname) VALUES (?, ?);";
	dao_status status = DAO_ERROR_UNKNOWN;

	do {
		if(sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
			status = DAO_ERROR_PREPARE;
			break;
		}

		if (sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC) != SQLITE_OK ||
			sqlite3_bind_text(stmt, 2, surname, -1, SQLITE_STATIC) != SQLITE_OK) {
			status = DAO_ERROR_BIND;
			break;
		}

		if(sqlite3_step(stmt) != SQLITE_DONE){
			status = DAO_ERROR_EXECUTE;
			break;
		}
		*out_new_id = (int) sqlite3_last_insert_rowid(db);
		status = DAO_SUCCESS;

	} while (0);

	if (stmt) {
		sqlite3_finalize(stmt);
	}
	return status;
}
// Read
int author_dao_check_existence(sqlite3 *db, const unsigned char *name, const unsigned char *surname) {
	sqlite3_stmt *stmt = NULL;
	const char *sql = "SELECT COUNT(*) FROM Author WHERE name = ? AND surname = ?";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		handle_dao_sql_error(DAO_ERROR_PREPARE);
		return -1;
	}
	if (sqlite3_bind_text(stmt, 1, (const char *) name, -1, SQLITE_STATIC) != SQLITE_OK ||
		sqlite3_bind_text(stmt, 2, (const char *) surname, -1, SQLITE_STATIC) != SQLITE_OK) {
		handle_dao_sql_error(DAO_ERROR_BIND);
		return -1;
	}

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		int count = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);
		return count == 1 ? 1 : 0;
	}

	sqlite3_finalize(stmt);
	return -1;
}

int author_dao_count(sqlite3 *db) {
	const char *sql = "SELECT COUNT(*) FROM Author";
	int count = 0;
	sqlite3_stmt *stmt;

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		handle_dao_sql_error(DAO_ERROR_PREPARE);
		goto null;
	}

	int rc = sqlite3_step(stmt);

	if (rc == SQLITE_ROW) {
		count = sqlite3_column_int(stmt, 0);
		if (!count) {
			handle_dao_sql_error(DAO_ERROR_EXECUTE);
			goto null;
		}
	}
	else {
		handle_dao_sql_error(DAO_ERROR_EXECUTE);
		goto null;
	}

	return count;
	null:
		if (stmt) {
			sqlite3_finalize(stmt);
		}
		return 0;
}

// returns objects in arena, do not free individually
Author** author_dao_find_all(DAOContext *ctx, Arena *a, int *out_count) {
	if (!a) return NULL;

	sqlite3 *db = db_get_handle(ctx);

	sqlite3_stmt *stmt = NULL;
	int author_size = author_dao_count(db);
	int rc, i = 0;

	if (author_size == 0) {
		handle_dao_sql_error(DAO_ERROR_NOT_FOUND);
		goto fail;
	}

	Author** authors = (Author**) malloc(sizeof(Author *) * author_size);

	if (!authors) { handle_dao_sql_error(DAO_ERROR_UNKNOWN); goto fail;}

	const char *sql = "SELECT id, name, surname FROM Author";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		handle_dao_sql_error(DAO_ERROR_PREPARE);
		goto fail;
	}

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		Author* author = author_create_in_arena(
			a,
			sqlite3_column_text(stmt, 1),
			sqlite3_column_text(stmt,2));
		if (!author) {
			handle_dao_sql_error(DAO_ERROR_UNKNOWN);
			goto fail;
		}
		author->id = sqlite3_column_int(stmt, 0);
		authors[i++] = author;
	}

	if (rc != SQLITE_DONE) {
		handle_dao_sql_error(DAO_ERROR_EXECUTE);
		goto fail;
	}

	sqlite3_finalize(stmt);
	if (out_count) *out_count = i;
	return authors;
	fail:
		if (stmt) sqlite3_finalize(stmt);
		if (authors == NULL) return NULL;

		for (int j = 0; j < i; j++) {
			if (authors[j] == NULL) {
				handle_dao_sql_error(DAO_ERROR_NOT_FOUND);
				return NULL;
			}
			free_author(authors[j]);
		}
		free(authors);
		return NULL;
}

// caller owns the object, must free
Author* author_dao_find_by_id(sqlite3 *db, Arena *a, int id) {
	if (!a) return NULL;

	sqlite3_stmt *stmt = NULL;
	Author *author = NULL;
	int rc;

	const char *sql = "SELECT *  FROM Author WHERE id =?";

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		handle_dao_sql_error(DAO_ERROR_PREPARE);
		goto fail;
	}

	if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK) {\
		handle_dao_sql_error(DAO_ERROR_BIND);
		goto fail;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		author = author_create_in_arena(a, sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2));

		if (!author) {
			handle_dao_sql_error(DAO_ERROR_UNKNOWN);
			goto fail;
		}
		author->id = sqlite3_column_int(stmt, 0);
	}
	else {
		handle_dao_sql_error(DAO_ERROR_EXECUTE);
		goto fail;
	}

	sqlite3_finalize(stmt);
	return author;

	fail:
		if (stmt) {
			sqlite3_finalize(stmt);
		}
		return NULL;
}

Author* author_dao_update(sqlite3 *db, Author *author, const unsigned char* name, const unsigned char* surname) {
	sqlite3_stmt *stmt = NULL;
	const char *sql = "UPDATE Author"
				   "SET name = ?, surname = ?"
					"WHERE id = ?";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		handle_dao_sql_error(DAO_ERROR_PREPARE);
		goto fail;
	}

	if (sqlite3_bind_text(stmt, 1, (const char *) name, -1, SQLITE_STATIC) != SQLITE_OK ||
		sqlite3_bind_text(stmt, 2,(const char *) surname, -1, SQLITE_STATIC) != SQLITE_OK ||
		sqlite3_bind_int(stmt, 3, author->id) != SQLITE_OK) {
		handle_dao_sql_error(DAO_ERROR_BIND);
		goto fail;
	}

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		handle_dao_sql_error(DAO_ERROR_EXECUTE);
		goto fail;
	}

	sqlite3_finalize(stmt);
	author->name = (char*) name;
	author->surname = (char *) surname;
	return author;
	fail:
		if (stmt) {
			sqlite3_finalize(stmt);
		}
		return NULL;
}

// // Delete
// failure_status  author_dao_delete_by_id(int id) {
// 	sqlite3_stmt *stmt = NULL;
// 	Author *author = NULL;
//
// 	author = author_dao_find_by_id(id);
// 	if (!author) {
// 		return FAIL_NOT_FOUND;
// 	}
//
// 	if (author_dao_check_existence((const unsigned char *)author->name, (const unsigned char *) author->surname) == 0) {
// 		return FAIL_NOT_FOUND;
// 	}
//
// 	const char *sql = "DELETE FROM Author WHERE id = ?";
//
// 	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
// 		free_author(author);
// 		return FAIL_PREPARE;
// 	}
//
// 	if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK) {
// 		free_author(author);
// 		return FAIL_BIND;
// 	}
//
// 	if (sqlite3_step(stmt) != SQLITE_DONE) {
// 		free_author(author);
// 		return FAIL_EXECUTE;
// 	}
//
// 	sqlite3_finalize(stmt);
// 	printf("Author: %s - %s was deleted", author->name, author->surname);
// 	return FAIL_NONE;
// }

dao_status author_dao_delete_all(sqlite3 *db) {
	sqlite3_stmt *stmt = NULL;
	const char *sql = "DELETE FROM Author";

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return DAO_ERROR_PREPARE;
	}

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return DAO_ERROR_EXECUTE;
	}

	sqlite3_finalize(stmt);
	return DAO_SUCCESS;
}