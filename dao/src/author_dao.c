#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

#include "author_dao.h"

#include <stdlib.h>

#include "author.h"
#include "db.h"

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
		default:
			msg = "Unknown error.";
	}

	fprintf(stderr, "%s %s\n", msg, sqlite3_errmsg(db));
}
// Create
failure_status author_dao_create(Author *author){
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
// failure_status author_dao_find_all(Author **authors, int *count) {
// 	const char *sql = "SELECT id, name, surname FROM Author";
// 	sqlite3_stmt *stmt;
// 	Author *author = NULL;
// 	int rc;
//
// 	author = (Author*) malloc(sizeof(Author));
// 	if (!author) {
// 		print_error("MALLOC-FAIL: Could not allocate memory for Author struct.\n");
// 	}
//
// 	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
// 		return FAIL_PREPARE;
// 	}
//
// 	sqlite3_finalize(stmt);
// 	return FAIL_NONE;
// }

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