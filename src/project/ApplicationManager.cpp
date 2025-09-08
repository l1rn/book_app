
#include <iostream>

#include "ApplicationManager.hpp"

extern "C"{
    #include "core/models/publisher.h"
    #include "core/models/author.h"
    #include "core/models/book.h"
    #include "core/dao/author_dao.h"
    #include "core/dao/publisher_dao.h"
    #include "core/dao/book_dao.h"

    #include "string.h"
    #include "sys/stat.h"
}

ApplicationManager::ApplicationManager(size_t arena_size, Environment env) : env_(env) {

}


bool ApplicationManager::file_exists(const char* path) {
    struct stat buffer{};
    return stat(path, &buffer) == 0;
}

void ApplicationManager::init_sample_authors() {
    Author sample_authors[] = {
        { .id = 0, .name = strdup("George"), .surname = strdup("Orwell") },
        { .id = 0, .name = strdup("Kostolom"), .surname = strdup("Mihail") },
        { .id = 0, .name = strdup("Kostolom"), .surname = strdup("LOLOLOWKA") }
    };

    size_t count = std::size(sample_authors);
    for (size_t i = 0; i < count; i++) {
        int id;
        if (author_dao_create(app_db_context, sample_authors[i].name, sample_authors[i].surname, &id) != DAO_SUCCESS) {
            std::cout << "\n" << "ID: " << id << "\n";
        }
    }
}

void ApplicationManager::init_sample_publishers() {
    Publisher sample_publishers[] = {
        { .company_name = strdup("Random House Worlds") }
    };
    int id;
    publisher_dao_create(app_db_context, sample_publishers[0].company_name, &id);
    std::cout << "["<< id << "]" << "Publisher created with name - " << sample_publishers[0].company_name;
}

void ApplicationManager::init_sample_books() {
    Book sample_books[] = {
        {
            .isbn13 = "9780553593716",
            .isbn10 = "0553593714",
            .book_name = strdup("A Game of Thrones"),
            .publication_date = "22.03.2011",
            .pages = 864,
            .publisher_id = 1
        }
    };
    book_dao_create(app_db_context,
        sample_books[0].isbn13,
        sample_books[0].isbn10,
        sample_books[0].book_name,
        sample_books[0].publication_date,
        sample_books[0].pages,
        sample_books[0].publisher_id);
    std::cout << "The book is created!";
}

void ApplicationManager::open_db() {
    const char *db_path = nullptr;
    const char *schema_path = nullptr;

    if (env_ == Environment::DEV) {
        db_path = "../data/local.db";
        schema_path = "../data/schemes/001_init.sql";
    }

    bool need_init = !file_exists(db_path);

    if (db_open(db_path, &app_db_context) != 0) {
        std::cerr << "Database open failed\n";
        db_close(app_db_context);
        return;
    }

    if (need_init) {
        if (db_init(app_db_context, schema_path) != 0) {
            std::cerr << "Database schema init failed.\n";
            db_close(app_db_context);
            return;
        }
        init_sample_authors();
        init_sample_publishers();
        init_sample_books();
        int count;
        book_dao_find_all(app_db_context, arena_.get(), &count);
    }
    else {
        std::cout << "Database already exists.\n";
    }
}

Arena *ApplicationManager::get_arena() {
    return arena_.get();
}

ArenaGuard &ApplicationManager::get_arena_guard() {
    return arena_;
}


void ApplicationManager::close_db() {
    db_close(app_db_context);
}

int ApplicationManager::open_app() {
    open_db();
    return 0;
}

int ApplicationManager::close_app() {
    close_db();
    return 0;
}