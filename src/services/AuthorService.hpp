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
    AuthorService(DAOContext *ctx, Arena *arena);

    void getAllAuthors(std::vector<Author>& out_authors);
    Author createAuthor(std::string name, std::string surname);

    void printAllAuthors();

private:
    DAOContext *ctx_;
    Arena *arena_;
};
#endif //BOOK_LIST_APP_AUTHOR_SERVICE_HPP