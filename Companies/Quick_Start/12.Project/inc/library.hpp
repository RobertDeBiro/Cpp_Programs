#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.hpp"
#include "constants.hpp"

class Library
{
public:
    Book books[LibConstants::max_books];
    int bookCount = 0;

    void addBook();
    void displayBooks();
    void borrowBook();
    void returnBook();
    void searchBook();
};

#endif // LIBRARY_H
