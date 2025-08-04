
#include <iostream>

extern "C"{
    #include "db.h"
    #include "author_dao.h"
    #include "author.h"
}

int handle_open() {
    if (db_open("../data/local.db") != 0) {
        std::cerr << "Database open failed\n";
        db_close();
        return 1;
    }

    if (db_init("../data/schemes/001_init.sql") == 0) {
        std::cout << "Database ready!\n";

        Author new_author = { .name = "George", .surname = "Orwell"  };

        if (author_dao_create(&new_author) != 0) {
            fprintf(stderr, "Failed to create author");
        }
        else {
            printf("Create author - %s, %s\n", new_author.name, new_author.surname);
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