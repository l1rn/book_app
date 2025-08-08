
#include <iostream>

extern "C"{
    #include "../db/db.h"
    #include "author_dao.h"
    #include "author.h"

    #include "string.h"
    #include "sys/stat.h"
}

static bool file_exists(const char* path) {
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

int handle_open() {
    const char *db_path = "../data/local.db";
    bool need_init = !file_exists(db_path);
    if (db_open(db_path) != 0) {
        std::cerr << "Database open failed\n";
        db_close();
        return 1;
    }

    if (need_init) {
        if (db_init("../data/schemes/001_init.sql") != 0) {
            std::cerr << "Database schema init failed.\n";
            db_close();
            return 1;
        }

        Author new_author = {
            .name = strdup("George"),
            .surname = strdup("Orwell")
        };

        Author new_author1 = {
            .name = strdup("Kostolom"),
            .surname = strdup("Mihail")
        };

        Author new_author2 = {
            .name = strdup("Kostolom"),
            .surname = strdup("LOLOLOWKA")
        };

        if (author_dao_create(&new_author) != 0) {
            fprintf(stderr, "Failed to create author");
        }

        if (author_dao_create(&new_author1) != 0) {
            fprintf(stderr, "Failed to create author");
        }

        if (author_dao_create(&new_author2) != 0) {
            fprintf(stderr, "Failed to create author");
        }

        free_author(&new_author);
        free_author(&new_author1);
        free_author(&new_author2);
    }
    else {
        std::cout << "Database already exists.\n";
    }

    int count = 0;
    Author **authors = author_dao_find_all(&count);
    if (authors) {
        for (int i = 0; i < count; i++) {
            printf("Author: %s %s\n", authors[i]->name, authors[i]->surname);
        }
        free_authors(authors, count);
    }
    db_close();
    return 0;
}