#include <iostream>
#include <string>
#include "../inc/library.hpp"
#include "../inc/book.hpp"

void Library::addBook()
{
    if (bookCount == LibConstants::max_books)
    {
        std::cout << "\n!!!!! Library is full. Cannot add more books. !!!!!\n\n";
        return;
    }

    Book newBook;
    std::cout << "Enter book title: ";
    std::getline(std::cin >> std::ws, newBook.title);

    for(int i = 0; i <= bookCount; i++)
    {
        if(books[i].title == newBook.title)
        {
            std::cout << "!!!!! Book already exist. !!!!!\n\n";
            return;
        }
    }    

    std::cout << "Enter author name: ";
    std::getline(std::cin >> std::ws, newBook.author);

    int genreChoice;
    std::cout << "Select genre (0 - Fiction, 1 - NonFiction, 2 - Mystery, 3 - SciFi, 4 - Fantasy): ";
    std::cin >> genreChoice;
    newBook.genre = static_cast<Genre>(genreChoice);

    newBook.available = true;

    books[bookCount] = newBook;
    bookCount++;

    std::cout << "\n+++++ Book added successfully! +++++\n\n";
}

void Library::displayBooks()
{
    if (bookCount == 0)
    {
        std::cout << "\n!!!!! No books in the library. !!!!!\n\n";
        return;
    }

    std::cout << "\n========== Library Books ==========\n";
    for (int i = 0; i < bookCount; i++)
    {
        std::cout << "Title: " << books[i].title << "\n";
        std::cout << "Author: " << books[i].author << "\n";
        std::cout << "Genre: " << getGenreString(books[i].genre) << "\n";
        std::cout << "Availability: " << (books[i].available ? "Available" : "Not Available") << "\n\n";
    }
}

void Library::borrowBook()
{
    if (bookCount == 0)
    {
        std::cout << "\n!!!!! No books in the library. !!!!!\n\n";
        return;
    }

    std::string searchTitle;
    std::cout << "Enter the title of the book you want to borrow: ";
    std::getline(std::cin >> std::ws, searchTitle);

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].title == searchTitle)
        {
            if (books[i].available)
            {
                books[i].available = false;
                std::cout << "\n+++++ Book \"" << searchTitle << "\" has been borrowed successfully. +++++\n\n";
            }
            else
            {
                std::cout << "\n!!!!! Book \"" << searchTitle << "\" is not available for borrowing. !!!!!\n\n";
            }
            return;
        }
    }

    std::cout << "\n!!!!! Book \"" << searchTitle << "\" not found in the library. !!!!!\n\n";
}

void Library::returnBook()
{
    if (bookCount == 0)
    {
        std::cout << "\n!!!!! This library didn't contain any book. !!!!!\n\n";
        return;
    }

    std::string searchTitle;
    std::cout << "Enter the title of the book you want to return: ";
    std::getline(std::cin >> std::ws, searchTitle);

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].title == searchTitle)
        {
            if (!books[i].available)
            {
                books[i].available = true;
                std::cout << "\n+++++ Book \"" << searchTitle << "\" has been returned successfully. +++++\n\n";
            }
            else
            {
                std::cout << "\n!!!!! Book \"" << searchTitle << "\" is already available in the library. !!!!!\n\n";
            }
            return;
        }
    }

    std::cout << "\n!!!!! Book \"" << searchTitle << "\" not found in the library. !!!!!\n\n";
}

void Library::searchBook()
{
    if (bookCount == 0)
    {
        std::cout << "\n!!!!! No books in the library. !!!!!\n\n";
        return;
    }

    std::string searchQuery;
    std::cout << "Enter the title of the book you want to search for: ";
    std::getline(std::cin >> std::ws, searchQuery);

    std::cout << "\n========== Search Results ==========\n";
    bool found = false;

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].title.find(searchQuery) != std::string::npos)
        {
            std::cout << "Title: " << books[i].title << "\n";
            std::cout << "Author: " << books[i].author << "\n";
            std::cout << "Genre: " << getGenreString(books[i].genre) << "\n";
            std::cout << "Availability: " << (books[i].available ? "Available" : "Not Available") << "\n\n";
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "\n!!!!! No books found matching the search criteria. !!!!!\n\n";
    }
}
