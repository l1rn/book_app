#include <iostream>

#include "author_service.hpp"

extern "C"{
#include "author.h"
#include "author_dao.h"
}

AuthorService::AuthorService(size_t arena_size) {

}

void AuthorService::printAllAuthors() {
    int count = 0;
    Author** authors = author_dao_find_all(arena_.get(), &count);

    if (!authors) {
        std::cerr << "No authors found or error occurred\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        std::cout << "Author[" << i << "]:"
            << authors[i]->name << " "
            << authors[i]->surname << "\n";
    }
}

