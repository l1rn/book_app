#ifndef BOOK_LIST_APP_AUTHOR_SERVICE_HPP
#define BOOK_LIST_APP_AUTHOR_SERVICE_HPP

extern "C"{
    #include "core/models/author.h"
}

#include "arena_guard.hpp"
#include <vector>

class AuthorService {
public:
    AuthorService(size_t arena_size = 64*1024);
    std::vector<Author> get_all_authors();
    void print_all_authors();

private:
    ArenaGuard arena_;
};
#endif //BOOK_LIST_APP_AUTHOR_SERVICE_HPP