//* Source files
/**
 *  - .cpp extension
 *  - compiled into object file
 **/

//* Header files
/**
 *  - .h or .hpp extensions, or no extension
 *  - introduced into source file
 *  - consists of two parts:
 *      1. Header guards
 *      2. Content
 *  - should have the same name as paired source file
 *  - can be included into source file by using:
 *      - angled brackets <>
 *      - quotes "" 
 **/

#include <iostream>
#include "../inc/add.hpp"

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}