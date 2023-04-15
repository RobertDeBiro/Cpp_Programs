/**
 * * Char data type
 *      - an integral type meaning the underlying value is stored as an integer, but interpreted as an
 *        ASCII (American Standard Code for Information Interchange) character
 *          - maps 127 integers to characters
 *      - we can initialize char variables using:
 *          - character literals
 *          - integers
 *      - in addition to ASCII there is Unicode standard which maps over 110 000 integers to characters
 *      - escape sequences are characters that have special meaning
 **/

#include <iostream>

int main()
{
    /*
     * Initialize char variable
     */
    // Initialize char with character
    char c1 = 'A';

    // Initialize char with integer number
    char c2 = 65;

    std::cout << "c1 = " << c1 << '\n';
    std::cout << "c2 = " << c2 << '\n';





    //////////////////////////////////////////////////////////////////

    /*
     * Input characters with std::cin
     */
    std::cout << "Please, input character: ";
    std::cin >> c1;

    return 0;
}