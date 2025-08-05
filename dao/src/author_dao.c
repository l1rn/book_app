#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

#include "author_dao.h"
#include "author.h"
#include "db.h"


void handle_sql_error(failure_status status) {
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
		default:
			msg = "Unknown error.";
	}

	fprintf(stderr, "%s %s\n", msg, sqlite3_errmsg(db));
}

failure_status author_create(Author *author){
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

failure_status author_find_by_id(Author *author) {
	const char *sql = "SELECT *  FROM Author WHERE id =?";
	sqlite3_stmt *stmt;

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		return FAIL_PREPARE;
	}

	if (sqlite3_bind_int(stmt, 1, author->id) != SQLITE_OK) {\
		sqlite3_finalize(stmt);
		return FAIL_BIND;
	}

	int rc  = sqlite3_step(stmt);
	if (rc == SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return FAIL_NOT_FOUND;
	}
	if (rc != SQLITE_ROW) {
		sqlite3_finalize(stmt);
		return FAIL_EXECUTE;
	}

	author->id = sqlite3_column_int(stmt, 0);
	author->name = strdup((const char*) sqlite3_column_text(stmt, 1));
	author->surname = strdup((const char*) sqlite3_column_text(stmt, 2));
	sqlite3_finalize(stmt);

	return FAIL_NONE;
}

// void author_dao_delete_by_id(int id) {
// 	const char *sql = "DELETE FROM Author WHERE id = ?";
// 	if (sqlite3_prepare_v2())
// }
