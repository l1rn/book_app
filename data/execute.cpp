
#include <iostream>

extern "C"{
    #include "db.h"
    #include "author_dao.h"
    #include "author.h"

    #include "string.h"
}

int handle_open() {
    if (db_open("../data/local.db") != 0) {
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

        if (author_dao_create(&new_author) != 0) {
            fprintf(stderr, "Failed to create author");
        }

        Author *author = author_dao_find_by_id(new_author.id);

        if (author == nullptr) {
            fprintf(stderr, "Failed to select author\n");
        }
        else {
            print_author(author);
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