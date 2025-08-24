#include <iostream>

#include "AuthorService.hpp"

extern "C"{
#include "author_dao.h"
}

AuthorService::AuthorService(DAOContext *ctx, Arena *arena) : ctx_(ctx), arena_(arena) {
    if (!ctx_) {
        std::cerr << "Invalid DAOContext provided to Author Service";
    }
}

Author AuthorService::createAuthor(std::string name, std::string surname) {
    long long author_id = 0;
    if (author_dao_create(ctx_, name.c_str(), surname.c_str(), &author_id) != DAO_SUCCESS) {

    }
    Author author;
    author.id = author_id;
    author.name = name.data();
    author.surname = surname.data();
    return author;
}

void AuthorService::getAllAuthors(std::vector<Author>& out_authors) {
    int count = 0;
    Author** authors = author_dao_find_all(ctx_, arena_, &count);
    out_authors.reserve(count);

    for (int i = 0; i < count; i++) {
        out_authors.push_back(*authors[i]);
    }
    free(authors);
}

void AuthorService::printAllAuthors() {
    std::vector<Author> authors;
    getAllAuthors(authors);
    for (const auto& author : authors) {
        std::cout << author.surname << "\n";
    }
}

