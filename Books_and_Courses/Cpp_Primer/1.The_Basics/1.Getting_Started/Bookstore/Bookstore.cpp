#include <iostream>
#include "Sales_item.h"

void exercise_1_20()
{
    Sales_item book;

    std::cout << "Insert book to store: \n";
    std::cin >> book;

    std::cout << "Books printout: \n";
    std::cout << book;
}

void exercise_1_21()
{
    Sales_item book1, book2;
    
    std::cout << "Insert book to store: \n";
    std::cin >> book1;

    std::cout << "Insert book to store, with the same ISBN: \n";
    std::cin >> book2;

    std::cout << "Books printout: \n";
    std::cout << book1 + book2;
}

int main()
{
    exercise_1_20();
    exercise_1_21();
    
    return 0;
}