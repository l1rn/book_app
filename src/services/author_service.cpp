#include <iostream>

#include "author_service.hpp"

extern "C"{
#include "author_dao.h"
}

AuthorService::AuthorService(size_t arena_size) {

}

std::vector<Author> AuthorService::get_all_authors() {
    int count = 0;
    Author** authors = author_dao_find_all(arena_.get(), &count);
    std::vector<Author> authors_vector;
    authors_vector.reserve(count);

    for (int i = 0; i < count; i++) {
        authors_vector.push_back(*authors[i]);
    }
    return authors_vector;
}

void AuthorService::print_all_authors() {
    std::vector<Author> authors = get_all_authors();
    for (const auto& author : authors) {
        std::cout << author.surname << "\n";
    }
}

