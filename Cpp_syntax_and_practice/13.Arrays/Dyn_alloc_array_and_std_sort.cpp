/*
 * LearnCpp
 * Arrays, Strings, and Dynamic Allocation
 * Dynamically allocating arrays
 */

#include <iostream>
#include <algorithm>
#include <string> // std::getline

int getAmountOfNames()
{
    std::cout << "How many names would you like to enter? ";
    int amount{};
    std::cin >> amount;
    return amount;
}

void enterNames(std::string* names, const int length)
{
    for(int i{ 0 }; i < length; i++)
    {
        std::cout << "Enter name #" << i + 1 << ": ";
        std::getline(std::cin >> std::ws, *(names + i));
    }
}

int main()
{
    std::cout << "*****************************************************\n";

    //********** Dynamically allocate array of strings **********
    const int length{ getAmountOfNames() };
    std::string* names{ new std::string[length] };

    // We cannot obtain size of dynamic array since it is a pointer
    // (just like we cannot obtain for decayed array since it is a pointer)
    //! unsigned int dyn_arr_length = std::size(names);

    enterNames(names, length);

    // std::sort(first_elem, last_elem)
    //  - sorts elements from 'first_elem' to 'last_elem'
    std::sort(names, names + length);

    std::cout << '\n' << "Here is sorted list:" << '\n';
    for(int i{ 0 }; i < length; i++)
    {
        std::cout << "Name #" << i + 1 << ": " << *(names + i) << '\n';
    }

    std::cout << '\n';

    delete[] names;

    std::cout << "*****************************************************\n";
    return 0;
}
