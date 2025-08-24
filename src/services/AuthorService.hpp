#ifndef BOOK_LIST_APP_AUTHOR_SERVICE_HPP
#define BOOK_LIST_APP_AUTHOR_SERVICE_HPP

extern "C"{
    #include "core/db/db.h"
    #include "core/models/author.h"
}

#include "ArenaGuard.hpp"
#include <vector>

class AuthorService {
public:
    explicit AuthorService(DAOContext *ctx, size_t arena_size = 64*1024);

    void getAllAuthors(std::vector<Author>& out_authors);
    Author createAuthor(std::string name, std::string surname);

    void printAllAuthors();

private:
    DAOContext *ctx_;
    ArenaGuard arena_;
};
#endif //BOOK_LIST_APP_AUTHOR_SERVICE_HPP