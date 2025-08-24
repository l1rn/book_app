#include <stdio.h>
#include <stdlib.h>
#include "db.h"

sqlite3 *db = NULL;

struct DAOContext {
    sqlite3 *db;
};

static char* read_file(const char* path) {
    FILE* file = fopen(path, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    size_t len = ftell(file);
    rewind(file);

    char* buffer = malloc(len + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }
    size_t read = fread(buffer, 1, len, file);

    if (read != len) {
        free(buffer);
        fclose(file);
        return NULL;
    }
    buffer[len] = '\0';
    fclose(file);
    return buffer;
}

int db_open(const char *filename, DAOContext **ctx_out){
    *ctx_out = malloc(sizeof(DAOContext));
    if (!(*ctx_out)) return 1;

    if(sqlite3_open(filename, &(*ctx_out)->db) != SQLITE_OK){
        free(ctx_out);
        fprintf(stderr, "DB open failed, %s\n", sqlite3_errmsg(db));
        return 1;
    }
    return 0;
}

int db_init(DAOContext *ctx, const char *schemaPath) {
    if (ctx == NULL) {
        fprintf(stderr, "Database not open. Call dbOpen first. \n");
        return 1;
    }

    char *schema = read_file(schemaPath);
    if (!schema) {
        fprintf(stderr, "Schema file not found%s\n", schemaPath);
        return 1;
    }
    char *errMsg = NULL;
    if (sqlite3_exec(db, schema, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Schema exec failed: %s\n", errMsg);
        sqlite3_free(errMsg);
        free(schema);
        return 1;
    }

    free(schema);
    return 0;
}

void db_close(DAOContext *ctx) {
    if (ctx) {
        sqlite3_close(ctx->db);
        free(ctx);
    }
}

sqlite3 *db_get_handle(DAOContext *ctx) {
    return ctx ? ctx->db : NULL;
}