//* Library Management System
/**
 * In this project, you will implement a simple command-line application to manage a library's book inventory.
 * The program will allow users to:
 *  - add books,
 *  - display book details,
 *  - borrow books,
 *  - return books,
 *  - search for books by title.
 * 
 * Hints - use:
 *  - multiple files (source and headers)
 *  - fundamental data types: int, string ...
 *  - user-defined data types: enums, structs, classes
 *  - flow control mechanisms: if-else, switch-case, while loop, for loop ...
 */

#include <iostream>
#include "../inc/library.hpp"

int main()
{
    Library library;
    int choice;

    do
    {
        std::cout << "========== Library Management System ==========" << std::endl;
        std::cout << "1. Add Book\n2. Display Books\n3. Borrow Book\n4. Return Book\n"
                  << "5. Search Book\n6. Exit\n";
        std::cout << "Enter your choice by choosing appropriate ordinal number: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                library.addBook();
                break;
            case 2:
                library.displayBooks();
                break;
            case 3:
                library.borrowBook();
                break;
            case 4:
                library.returnBook();
                break;
            case 5:
                library.searchBook();
                break;
            case 6:
                std::cout << "Thank you for using the Library Management System. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (true);

    return 0;
}
