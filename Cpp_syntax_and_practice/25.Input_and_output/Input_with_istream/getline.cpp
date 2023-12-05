#include <iostream>
#include <limits> // std::numeric_limits

int main()
{
    std::cout << "*****************************************************\n";

    // Read up to 10 more characters
    //  - when typing e.g. "Hello!", everything will be saved inside input buffer,
    //    together with whitespace characters and newline
    //  - in this way we are avoiding the issue appeared in cin_get() function 
    char strBuf[11];
    std::cout << "Please, type Hello!:\n";
    std::cin.getline(strBuf, 11);
    std::cout << strBuf << '\n';

    std::cout << "---------------------------------------------\n";

    // Read up to 10 more characters
    std::cout << "Please, type Hello!:\n";
    std::cin.getline(strBuf, 11);
    std::cout << strBuf << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
