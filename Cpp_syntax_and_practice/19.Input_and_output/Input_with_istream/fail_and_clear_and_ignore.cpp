/*
 * template<
 *  class CharT,
 *  class Traits = std::char_traits<CharT>
 * > class basic_istream : virtual public std::basic_ios<CharT, Traits>
 *
 *  - std::cin is object of a "basic_istream" class
 *  - basic_istream class is included in <iostrem> library
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/io/basic_istream
 */

#include <iostream>
#include <limits> // std::numeric_limits

int main()
{
    std::cout << "*****************************************************\n";

    int number{};
    do
    {
        std::cout << "Enter a number between 1 and 9: ";
        std::cin >> number;

        // If the user entered something invalid, e.g. letter, std::cin.fail() returns true
        if (std::cin.fail())
        {
            std::cin.clear(); // reset any error flags
        }
        // Ignore every character in the buffer until encountering newline (\n)
        //  - for example, if we enter "4k kk", extraction operator won't fail,
        //    and "k kk" will be ignored when encountering next std::cout and insertion operator (<<)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while(number < 1 || number > 9);

    std::cout << "Number " << number << " is in proper scope!\n";

    std::cout << "*****************************************************\n";
    return 0;
}
