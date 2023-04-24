#include <iostream>

int main()
{
    //* Char
    /**
     *  - an integral type meaning the underlying value is stored as an integer, but interpreted as an
     *    ASCII (American Standard Code for Information Interchange) character
     *      - maps 127 integers to characters
     *  - we can initialize char variables using:
     *      - character literals
     *      - integers
     **/
    // Initialize char with character
    char c1 = 'A';

    // Initialize char with number character
    char c2 = '6';
    int i = c2;

    // Initialize char with integer number
    char c3 = 65;

    std::cout << "c1 = " << c1 << '\n';
    std::cout << "c2 = " << c2 << '\n';
    std::cout << "i = " << i << '\n';
    std::cout << "c3 = " << c3 << '\n';

    //////////////////////////////////////////////////////////////////

    //* Input characters with std::cin
    std::cout << "Please, input character: ";
    std::cin >> c1;
    std::cout << "c1 = " << c1 << '\n';
    std::cin >> c1;
    std::cout << "c1 = " << c1 << '\n';
    
    std::cin >> c1;
    std::cout << "c1 = " << c1 << '\n';
    std::cin >> c1;
    std::cout << "c1 = " << c1 << '\n';
    std::cin >> c1;
    std::cout << "c1 = " << c1 << '\n';
    std::cin >> c1;
    std::cout << "c1 = " << c1 << '\n';

    //////////////////////////////////////////////////////////////////

    //* Escape sequence
    //std::cout << "Printing string "Hello" " << '\n';
    std::cout << "Printing string \"Hello\" " << '\n';

    //std::cout << "Printing backslash \" << '\n';
    std::cout << "Printing backslash \\" << '\n';

    return 0;
}