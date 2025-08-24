
#include <iostream>

#include "ExecuteManager.hpp"
#include "AuthorService.hpp"

extern "C"{
    #include "author.h"

    #include "string.h"
    #include "sys/stat.h"
}

ExecuteManager::ExecuteManager(size_t arena_size, Environment env) : env_(env) {

}


bool ExecuteManager::file_exists(const char* path) {
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

void ExecuteManager::init_sample_authors() {
    Author sample_authors[] = {
        { .id = 0, .name = strdup("George"), .surname = strdup("Orwell") },
        { .id = 0, .name = strdup("Kostolom"), .surname = strdup("Mihail") },
        { .id = 0, .name = strdup("Kostolom"), .surname = strdup("LOLOLOWKA") }
    };

    size_t count = std::size(sample_authors);
}

void ExecuteManager::open_db() {
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
        if (env_ == Environment::DEV) {
            init_sample_authors();
        }
    }
    else {
        std::cout << "Database already exists.\n";
    }
}

void ExecuteManager::close_db() {
    db_close(app_db_context);
}

int ExecuteManager::open_app() {
    open_db();
    return 0;
}

int ExecuteManager::close_app() {
    close_db();
    return 0;
}