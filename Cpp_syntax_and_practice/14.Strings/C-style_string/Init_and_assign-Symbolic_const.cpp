#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    //********** Initialize C-style string symbolic constant **********
    const char* hello1{ "Hello, hello world!" };

    while(*hello1 != '\0')
    {
        std::cout << *hello1;
        hello1++;
    }
    std::cout << '\n';

    // We cannot print C-style string symbolic constant by using for-each loop
    //  - for-each can be only used for arrays
    //! for(const auto elem : hello1)
    //!     std::cout << elem;
    //! std::cout << '\n';

    // Following line will be compiled, but warning will appear that 'const' string literal
    // must be assigned to const char* not char*
    //  - every literal value is 'const'
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
