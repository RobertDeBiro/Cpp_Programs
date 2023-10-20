#include <iostream>
#include <cstring> // strcpy

int main()
{
    std::cout << "*****************************************************\n";

    //****** Initialize C-style string *****
    // Initialize char array with C-style string
    // - C++ automatically adds a null terminator
    char hello[] { "Hello, world!"};


    //****** Print C-style string *****
    // We can print C-style string either by:
    // 1) Using loop
    for(const auto elem : hello)
        std::cout << elem;
    
    std::cout << '\n';

    // 2) Using only std::cout
    //     - std::cout prints characters until it encounters the null terminator
    std::cout << hello << '\n';


    //***** Update character in C-style string *****
    hello[0] = 'B';
    std::cout << hello << '\n';


    //***** Assign C-style string *****
    // Assign C-style string to char array
    //  - when we want to assign a value to char array, we need to use strcpy
    std::strcpy(hello, "Sleep, world!");
    std::cout << hello << '\n';

    // We cannot assign a value to a C-style array after initializing!
    //!hello = "Sleep, world!"

    std::cout << "*****************************************************\n";
    return 0;
}
