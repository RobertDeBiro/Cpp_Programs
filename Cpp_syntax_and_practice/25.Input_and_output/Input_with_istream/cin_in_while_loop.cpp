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
    int num, sum, counter = 0;
    // the extraction operator (>>) skips the whitespaces and the newline i.e. 
    // 'std::cin' reads everything until it encounters whitespace or newline
    // - everything entered after whitespace or newline is saved into the buffer and read in next
    //   while iteration
    while (std::cin >> num)
    {
        sum += num;
        std::cout << ++counter << ". iteration\n";
    }
    std::cout << "Final sum: " << sum << std::endl;

    std::cout << "---------------------------------\n";
    std::cin.clear();

    std::cout << "Continuously enter characters to char variable and print them: ";
    char ch;
    counter = 0;
    // extraction operator (>>) won't put multiple characters into 'ch', he knows that 'ch'
    // can receive only one character, so it buffers other characters for next iteration
    while (std::cin >> ch)
    {
        std::cout << ch;
        std::cout << ++counter << ". iteration\n";
    }

    std::cout << "*****************************************************\n";
    return 0;
}