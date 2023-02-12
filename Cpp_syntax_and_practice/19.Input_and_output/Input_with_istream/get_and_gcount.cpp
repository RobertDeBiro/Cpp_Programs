/*
 * References:
 *  - https://en.cppreference.com/w/cpp/io/basic_istream/get
 */

#include <iostream>
#include <iomanip> // std::setw
#include <limits> // std::numeric_limits

int main()
{
    std::cout << "*****************************************************\n";

    // When typing "Hello, my name is Robert de Biro!", everything will be saved inside input buffer
    // except whitespace characters, since the extraction operator (>>) skips whitespace
    // (blanks, tabs, and newlines) 
    //  - hence, "Hello,mynameisRobertdeBiro" will be printed to the screen
    //  - "ch != '!" is used so we don't have to manually break the while loop 
    char ch;
    std::cout << "Please, type some sentence (whitespaces won't be saved):\n";
    while (std::cin >> ch && ch != '!')
        std::cout << ch;

    // Remove "!" and newline characters that left from previous input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n--------------------------------\n";

    // Save whitespaces, but don't save newline
    std::cout << "Please, type some sentence (whitespaces will be saved):\n";
    while (std::cin.get(ch) && ch != '!')
        std::cout << ch;
    
    // Ignore newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n--------------------------------\n";

    // Restrict number of characters saved in input buffer
    //  - the same feature as std::setw, except std::cin.get() includes also whitespaces
    //  - input: Hello, my name is Robert
    //  - output: "Hello, my " + null terminator at the end 
    char strBuf1[11];
    std::cout << "Please, type sentence more than 11 characters (output will be restricted to 10 chars)!:\n";
    std::cin.get(strBuf1, 11);
    std::cout << strBuf1 << '\n';
    // Retrieve how many characters were extracted by the last usage of std::cin
    std::cout << std::cin.gcount() << " characters were read" << '\n';

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "--------------------------------\n";

    // Read up to 10 characters
    char strBuf2[11];
    std::cout << "Please, type Hello!:\n";
    std::cin.get(strBuf2, 11);
    std::cout << strBuf2 << '\n';
    
    // Read up to 10 more charachters
    // - only newline will be read (newline from previous input), hence nothing will be printed
    std::cin.get(strBuf2, 11);
    std::cout << strBuf2 << '\n';
    std::cout << std::cin.gcount() << " characters were read" << '\n';

    std::cout << "--------------------------------\n";

    // Since std::cin.get collected in strBuf only newline, error appeared (but not showed)
    // and needs to be cleared
    std::cin.clear();

    std::cout << "*****************************************************\n";
    return 0;
}
