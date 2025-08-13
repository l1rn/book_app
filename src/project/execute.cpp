
#include <iostream>

#include "main_window.hpp"

extern "C"{
    #include "db.h"
    #include "author_dao.h"
    #include "author.h"

    #include "string.h"
    #include "sys/stat.h"
}

namespace {
    bool file_exists(const char* path) {
        struct stat buffer;
        return stat(path, &buffer) == 0;
    }

    void init_sample_authors() {
        Author sample_authors[] = {
        { .name = strdup("George"), .surname = strdup("Orwell") },
        { .name = strdup("Kostolom"), .surname = strdup("Mihail") },
        { .name = strdup("Kostolom"), .surname = strdup("LOLOLOWKA") }
        };

        size_t count = std::size(sample_authors);

        for (size_t i = 0; i < count; i++) {
            if (author_dao_create(&sample_authors[i]) != 0) {
                std::cerr << "Failed to create author: "
                    << sample_authors->name << ", "
                    << sample_authors->surname << "\n";
            }
            free_author(&sample_authors[i]);
        }
    }

    void print_authors() {
        int count = 0;
        Author **authors = author_dao_find_all(&count);
        if (authors) {
            for (int i = 0; i < count; i++) {
                printf("Author: %s %s\n", authors[i]->name, authors[i]->surname);
            }
            free_authors(authors, count);
        }
    }
}


int handle_db() {
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
        init_sample_authors();
    }
    else {
        std::cout << "Database already exists.\n";
    }
    print_authors();
    return 0;
}