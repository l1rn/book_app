#include <stdio.h>
#include <stdlib.h>
#include "db.h"

sqlite3 *db = NULL;

static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
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

int db_open(const char *filename){
    if(sqlite3_open(filename, &db) != SQLITE_OK){
        fprintf(stderr, "DB open failed, %s\n", sqlite3_errmsg(db));
        return 1;
    }
    printf("DB open!\n");
    return 0;
}

int db_check() {
    if (db != NULL) {
        return 0;
    }
    return 1;
}

int db_init(const char *schemaPath) {
    if (db == NULL) {
        fprintf(stderr, "Database not open. Call dbOpen first. \n");
        return 1;
    }

    char *schema = readFile(schemaPath);
    if (!schema) {
        fprintf(stderr, "Schema file not found%s\n", schemaPath);
        return 1;
    }
    printf("%s", schema);
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

void db_close(void) {
    if (db) sqlite3_close(db);
}