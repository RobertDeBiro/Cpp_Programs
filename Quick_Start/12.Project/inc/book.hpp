#ifndef BOOK_H
#define BOOK_H

#include <string>

enum Genre
{
    Fiction,
    NonFiction,
    Mystery,
    SciFi,
    Fantasy
};

struct Book
{
    std::string title;
    std::string author;
    Genre genre;
    bool available;
};

std::string getGenreString(Genre genre);

#endif // BOOK_H
