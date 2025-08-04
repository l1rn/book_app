#include <sqlite3.h>
#include <stdio.h>

#include "/home/lirn/CLionProjects/book_app/dao/include/author_dao.h"
#include "/home/lirn/CLionProjects/book_app/models/include/author.h"
#include "/home/lirn/CLionProjects/book_app/data/db.h"

int author_dao_create(Author *author){
	const char *sql = "INSERT INTO Author (name, surname) VALUES (?, ?);";
	sqlite3_stmt *stmt;	
	if(sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
		fprintf(stderr, "SQL prepare failed %s\n", sqlite3_errmsg(db));
		return 1;
	}

	sqlite3_bind_text(stmt, 1, author->name, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, author->surname, -1, SQLITE_STATIC);

	if(sqlite3_step(stmt) != SQLITE_DONE){
		fprintf(stderr, "SQL execution failed: %s\n", sqlite3_errmsg(db));
		return 1;
	}

	author->id = (int) sqlite3_last_insert_rowid(db);
	sqlite3_finalize(stmt);
	return 0;
}
