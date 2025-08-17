//
// Created by Администратор on 8/17/2025.
//

#ifndef BOOK_LIST_APP_AUTHOR_SERVICE_HPP
#define BOOK_LIST_APP_AUTHOR_SERVICE_HPP

#include "arena_guard.hpp"

class AuthorService {
public:
    AuthorService(size_t arena_size = 64*1024);
    void printAllAuthors();

private:
    ArenaGuard arena_;
};
#endif //BOOK_LIST_APP_AUTHOR_SERVICE_HPP