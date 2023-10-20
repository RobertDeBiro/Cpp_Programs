#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    //****** Initialize C-style string *****
    // Initialize symbolic constant
    //  - variable of type " const char* " that has C-style string assign to it
    //    is called symbolic constant (because it is const)
    //  - the compiler places the string "Hello, world!\0" into read-only memory somewhere,
    //    and then sets the pointer to point to it
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

    std::cout << "*****************************************************\n";
    return 0;
}
