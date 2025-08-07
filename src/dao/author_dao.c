#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "author_dao.h"

#include <stdlib.h>

#include "author.h"
#include "db.h"

int author_dao_check_existence(const unsigned char *name, const unsigned char *surname);

void handle_dao_sql_error(failure_status status) {
	const char *msg = NULL;
	switch (status) {
		case FAIL_PREPARE:
			msg = "SQL prepare failed.";
			break;
		case FAIL_EXECUTE:
			msg = "SQL execution failed.";
			break;
		case FAIL_BIND:
			msg = "SQL bind failed.";
			break;
		case FAIL_NOT_FOUND:
			msg  = "Record not found.";
			break;
		case FAIL_MEMORY_ALLOC:
			msg = "Unable to allocate memory";
			break;
		case FAIL_ALREADY_EXIST:
			msg = "Record already exist";
			break;
		default:
			msg = "Unknown error.";
	}

	fprintf(stderr, "%s %s\n", msg, sqlite3_errmsg(db));
}

// Create
failure_status author_dao_create(Author *author){
	if (author_dao_check_existence((const unsigned char *) author->name, (const unsigned char *) author->surname) == 1) {
		handle_dao_sql_error(FAIL_ALREADY_EXIST);
		return FAIL_NONE;
	}
	const char *sql = "INSERT INTO Author (name, surname) VALUES (?, ?);";
	sqlite3_stmt *stmt;

	if(sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
		return FAIL_PREPARE;
	}

	if (sqlite3_bind_text(stmt, 1, author->name, -1, SQLITE_STATIC) != SQLITE_OK ||
		sqlite3_bind_text(stmt, 2, author->surname, -1, SQLITE_STATIC) != SQLITE_OK) {
		sqlite3_finalize(stmt);
		return FAIL_BIND;
	}

	if(sqlite3_step(stmt) != SQLITE_DONE){
		return FAIL_EXECUTE;
	}

	author->id = (int) sqlite3_last_insert_rowid(db);
	sqlite3_finalize(stmt);
	return FAIL_NONE;
}

// Read
int author_dao_check_existence(const unsigned char *name, const unsigned char *surname) {
	sqlite3_stmt *stmt = NULL;
	const char *sql = "SELECT COUNT(*) FROM Author WHERE name = ? AND surname = ?";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		handle_dao_sql_error(FAIL_PREPARE);
		return NULL;
	}
	if (sqlite3_bind_text(stmt, 1, (const char *) name, -1, SQLITE_STATIC) != SQLITE_OK ||
		sqlite3_bind_text(stmt, 2, (const char *) surname, -1, SQLITE_STATIC) != SQLITE_OK) {
		handle_dao_sql_error(FAIL_BIND);
		return NULL;
	}

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		sqlite3_finalize(stmt);
		if (sqlite3_column_int(stmt, 0) == 1) {
			return 1;
		}
		return 0;
	}

	sqlite3_finalize(stmt);
	return 0;
}

int author_dao_count() {
	const char *sql = "SELECT COUNT(*) FROM Author";
	int count = 0;
	sqlite3_stmt *stmt;

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		handle_dao_sql_error(FAIL_PREPARE);
		goto null;
	}

	int rc = sqlite3_step(stmt);

	if (rc == SQLITE_ROW) {
		count = sqlite3_column_int(stmt, 0);
		if (!count) {
			handle_dao_sql_error(FAIL_EXECUTE);
			goto null;
		}
	}
	else {
		handle_dao_sql_error(FAIL_EXECUTE);
		goto null;
	}

	return count;
	null:
		if (stmt) {
			sqlite3_finalize(stmt);
		}
		return 0;
}

Author** author_dao_find_all(int *out_count) {
	sqlite3_stmt *stmt = NULL;
	int author_size = author_dao_count();
	Author** authors = NULL;
	int rc, i = 0;

	if (author_size == 0) {
		handle_dao_sql_error(FAIL_NOT_FOUND);
		goto fail;
	}
	authors = (Author**) malloc(sizeof(Author *) * author_size);

	if (!authors) {
		handle_dao_sql_error(FAIL_MEMORY_ALLOC);
		goto fail;
	}

	const char *sql = "SELECT id, name, surname FROM Author";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		handle_dao_sql_error(FAIL_PREPARE);
	}

	rc = sqlite3_step(stmt);

	if (rc != SQLITE_ROW){
		handle_dao_sql_error(FAIL_EXECUTE);
		goto fail;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		Author* author = author_create_model(
			sqlite3_column_text(stmt, 1),
			sqlite3_column_text(stmt,2));
		if (!author) {
			handle_dao_sql_error(FAIL_MEMORY_ALLOC);
			goto fail;
		}
		author->id = sqlite3_column_int(stmt, 0);
		authors[i++] = author;
	}

	sqlite3_finalize(stmt);
	if (out_count) *out_count = i;
	return authors;
	fail:
		if (stmt) sqlite3_finalize(stmt);
		for (int j = 0; j < i; j++) {
			if (authors[j] == NULL) {
				handle_dao_sql_error(FAIL_NOT_FOUND);
				return NULL;
			}
			free_author(authors[j]);
		}
		free(authors);
		return NULL;
}

Author* author_dao_find_by_id(int id) {
	sqlite3_stmt *stmt = NULL;
	Author *author = NULL;
	int rc;

	author = (Author *) malloc(sizeof(Author));
	if (!author) {
		handle_dao_sql_error(FAIL_MEMORY_ALLOC);
		goto fail;;
	}

	author->name = NULL;
	author->surname = NULL;

	const char *sql = "SELECT *  FROM Author WHERE id =?";

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		handle_dao_sql_error(FAIL_PREPARE);
		goto fail;
	}

	if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK) {\
		handle_dao_sql_error(FAIL_BIND);
		goto fail;
	}

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		author = author_create_model(sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2));

		if (!author->name || !author->surname) {
			handle_dao_sql_error(FAIL_EXECUTE);
			goto fail;
		}
	}
	else {
		handle_dao_sql_error(FAIL_EXECUTE);
		goto fail;
	}

	sqlite3_finalize(stmt);
	return author;

	fail:
		if (stmt) {
			sqlite3_finalize(stmt);
		}
		if (author) {
			free(author->name);
			free(author->surname);
			free(author);
		}
		return NULL;
}