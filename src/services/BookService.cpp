//
// Created by l1rn
//

#include "BookService.h"

#include <iostream>

BookService::BookService(DAOContext *ctx, Arena *a) : _ctx(ctx), _a(a){
    if (!ctx) {
        std::cerr << "Invalid DAOContext!";
    }
}


Book BookService::createBook(
    std::string isbn13,
    std::string isbn10,
    std::string bookName,
    std::string publicationDate,
    int pages,
    int publisherId) {
    if (!book_dao_create(
        _ctx,
        isbn13.c_str(),
        isbn10.c_str(),
        bookName.c_str(),
        publicationDate.c_str(),
        pages,
        publisherId)) {
        std::cerr <<  "Fail to create Book ISBN13 - " << isbn13;
    }

    Book book;
    strcpy(book.isbn13, isbn13.c_str());
    strcpy(book.isbn10, isbn13.c_str());
    book.book_name = bookName.data();
    strcpy(book.publication_date, publicationDate.c_str());
    book.pages = pages;
    book.publisher_id = publisherId;
    return book;
}

void BookService::getAllBooks(std::vector<Book>& out_books) {
    int count = 0;
    Book **books = book_dao_find_all(_ctx, _a, &count);
    if (!books) {
        std::cerr << "Failed to get books";
        return;
    }
    out_books.reserve(count);
    for (int i = 0; i < count; i++) {
        out_books.push_back(*books[i]);
    }
    free(books);
}

void BookService::printAllBooks() {
    std::vector<Book> books;
    getAllBooks(books);
    for (const auto& book : books) {
        std::cout << "[isbn13" << book.isbn13 << "] "
        << ", name: " << book.book_name
        << ", isbn10: " << book.isbn10
        << ", publication date: " << book.publication_date
        << ", pages: " << book.pages
        << "\n";
    }
}