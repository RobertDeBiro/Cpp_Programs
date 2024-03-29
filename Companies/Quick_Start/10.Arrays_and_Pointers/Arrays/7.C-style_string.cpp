//* C-style strings
/**
 *  - array of characters that uses a null terminator
 *      - a null terminator is a special character (‘\0’, ASCII code 0) used to indicate the end of the string
 *  - hence, C-style string is also called a null-terminated string
 *  - C++ automatically adds null terminator at the
 *  - syntax:
 *?     char myString[]{ "string" }
 **/

#include <iostream>
#include <cstring>

int main()
{
    // C-style string is actually an array typed with char, that automatically adds null character at the end
    char name1[]{ "John" };
    std::cout << name1 << '\n';

    // Initialize char array with initialization list
    char name2[4]{ 'J', 'o', 'h', 'n' };            // Prints undefined string
    std::cout << name2 << '\n';

    char name3[5]{ 'J', 'o', 'h', 'n', '\0' };      // Adding null character at the end
    std::cout << name3 << '\n';


    //* Manipulating C-style strings
    //  - C++ provides many functions to manipulate C-style strings as part of <cstring> library, such as:
    //      - strcpy
    //      - strcat
    //      - strcmp
    // char name4[std::size(name1)] = name1;
    char name4[std::size(name1)];   // size should be 5
    strcpy(name4, name1);
    std::cout << name4 << '\n';

    // strcat
    char surname1[]{ " Rashford" };
    std::cout << "Name and surname: " << strcat(name1, surname1) << '\n';

    return 0;
}