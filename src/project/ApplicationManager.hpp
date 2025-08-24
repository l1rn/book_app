
#ifndef EXECUTE_H
#define EXECUTE_H

#include "services/ArenaGuard.hpp"
extern "C"{
    #include "core/db/db.h"
}

enum Environment {
    DEV,
    PROD
};

class ApplicationManager {
public:
    explicit ApplicationManager(size_t arena_size = 64*1024, Environment env = Environment::DEV);
    ~ApplicationManager() = default;

    int open_app();
    DAOContext *get_context() { return app_db_context; }
    Arena *get_arena();
    ArenaGuard& get_arena_guard();

    int close_app();
private:
    Environment env_;

    ArenaGuard arena_{64 * 1024};
    DAOContext *app_db_context;

    static bool file_exists(const char* path);

    static void init_sample_authors();

    void open_db();

    void close_db();
};

#endif
