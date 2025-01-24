#include "Book.h"

#include <iostream>

Book::Book(const std::string& title, const std::string& isbn)
    : Media(title, MediaType::BOOK), isbn(isbn) {}

std::string Book::getIsbn() const {
    return isbn;
}

void Book::displayDetails() const {
    std::cout << "--- Livre ---\n";
    Media::displayDetails();
    std::cout << "ISBN : " << isbn << std::endl;
}