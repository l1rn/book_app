
#include <iostream>

extern "C"{
    #include "../db/db.h"
    #include "author_dao.h"
    #include "author.h"

    #include "string.h"
}

int handle_open() {
    if (db_open("local.db") != 0) {
        std::cerr << "Database open failed\n";
        db_close();
        return 1;
    }

    if (db_init("../data/schemes/001_init.sql") == 0) {
        std::cout << "Database ready!\n";

        Author new_author = {
            .name = strdup("George"),
            .surname = strdup("Orwell")
        };

        Author new_author1 = {
            .name = strdup("Kostolom"),
            .surname = strdup("Mihail")
        };

        if (author_dao_create(&new_author) != 0) {
            fprintf(stderr, "Failed to create author");
        }

        if (author_dao_create(&new_author1) != 0) {
            fprintf(stderr, "Failed to create author");
        }

        int count = 0;
        Author **authors = author_dao_find_all(&count);

        if (authors) {
            for (int i = 0; i < count; i++) {
                printf("Author: %s %s\n", authors[i]->name, authors[i]->surname);
                free_author(authors[i]);
            }
            free(authors);
        }
    }
    else {
        std::cerr << "Database schema init failed.\n";
        db_close();
        return 1;
    }
    db_close();
    return 0;
}