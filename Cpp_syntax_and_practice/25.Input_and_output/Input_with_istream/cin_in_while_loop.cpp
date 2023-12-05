/*
 * In order to go out from the loop we must enter::
 *  1. Ctrl + Z
 *  2. Enter
 */

#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    std::cout << "Continuously enter integer numbers to sum: ";
    int num, sum;
    while (std::cin >> num)
        sum += num;
    std::cout << "Final sum: " << sum << std::endl;

    std::cout << "---------------------------------\n";
    std::cin.clear();

    // the extraction operator (>>) skips the spaces and the newline
    std::cout << "Continuously enter characters to char variable and print them: ";
    char ch;
    while (std::cin >> ch)
        std::cout << ch;

    std::cout << "*****************************************************\n";
    return 0;
}