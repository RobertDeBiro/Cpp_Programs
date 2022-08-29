#include <iostream>
#include <cstring> // strcpy

void initialization_and_assignment();
void C_style_string_symbolic_constant();

int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();
    C_style_string_symbolic_constant();

    std::cout << "*****************************************************\n";
    return 0;
}

void initialization_and_assignment()
{
    // Initializing C-style string
    //  - C++ automatically adds a null terminator
    char hello[] { "Hello, world!"};

    // We can print C-style string either by using loop, or by using only std::cout
    //  - std::cout prints characters until it encounters the null terminator
    for(const auto elem : hello)
        std::cout << elem;
    std::cout << '\n';
    std::cout << hello << '\n';

    // Update character in C-style string
    hello[0] = 'B';
    std::cout << hello << '\n';
    
    // When we want to assign a value to char array, we need to use strcpy
    //  - we cannot assign a value to a C-style array after initializing!
    //    hello1 = "Sleep, world!"
    std::strcpy(hello, "Sleep, world!");
    std::cout << hello << '\n';

    std::cout << "------------------------------\n";
}

void C_style_string_symbolic_constant()
{
    // C-style string symbolic constant
    //  - the compiler places the string "Hello, world!\0" into read-only memory somewhere, and then sets the pointer to point to it
    //  - since the string is inside read-only memory, best practice is to make sure the string is const
    //  - C++ automatically adds a null terminator
    const char* hello1{ "Hello, hello world!" };

    while(*hello1 != '\0')
    {
        std::cout << *hello1;
        hello1++;
    }
    std::cout << '\n';

    // We cannot print C-style string symbolic constant by using for-each loop
    //  - for-each can be only used for arrays
    //
    // for(const auto elem : hello2)
    //     std::cout << elem;
    // std::cout << '\n';

    // Following line will be compiled, but warning will appear that string literal must be assigned to const char* not char*
    char* hello2{ "Hello, hello, hello world"};
    while(*hello2 != '\0')
    {
        std::cout << *hello2;
        hello2++;
    }
    std::cout << '\n';

    std::cout << "------------------------------\n";
}