
#ifndef EXECUTE_H
#define EXECUTE_H
#include "services/arena_guard.hpp"

class Execute {
public:
    explicit Execute(size_t arena_size = 64*1024);
    ~Execute() = default;

    int open_app();

    static int close_app();
private:
    ArenaGuard arena_;

    static bool file_exists(const char* path);

    static void init_sample_authors();
    void open_db();
};

#endif
