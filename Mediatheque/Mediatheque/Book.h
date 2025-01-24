#ifndef BOOK_H
#define BOOK_H

#include "Media.h"
#include <string>

class Book : public Media {
private:
    std::string isbn;

public:
    Book(const std::string& title, const std::string& isbn);

    std::string getIsbn() const;
    void displayDetails() const override;
};

#endif // BOOK_H