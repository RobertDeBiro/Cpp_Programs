#include "../inc/book.hpp"

std::string getGenreString(Genre genre)
{
    switch (genre)
    {
        case Genre::Fiction:    return "Fiction";
        case Genre::NonFiction: return "NonFiction";
        case Genre::Mystery:    return "Mystery";
        case Genre::SciFi:      return "SciFi";
        case Genre::Fantasy:    return "Fantasy";
        default:                return "Unknown genre";
    }
}
