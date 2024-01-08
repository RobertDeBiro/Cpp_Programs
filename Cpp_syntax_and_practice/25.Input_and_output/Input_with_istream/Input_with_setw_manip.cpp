/*
 * setw(int n)
 *  - setw = set width
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/io/manip/setw
 */

#include <iostream>
#include <iomanip>
#include <limits> // std::numeric_limits

int main()
{
    std::cout << "*****************************************************\n";

    // When typing "MoreThenTenChars", everything is fine,
    // even though it shouldn't be since 16 characters are generated
    //  - maybe this works in my compiler, but in some others maybe it won't work
    char buf1[10];
    std::cout << "Type in more then 10 characters (without space): \n";
    std::cin >> buf1;
    std::cout << buf1;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << '\n';
    std::cout << "\n---------------------------------\n";

    // Retrieve 10 characters placed inside 'std::cin' buffer, and put them into a variable
    char buf2[10];
    std::cout << "Type in more then 10 characters (without space): \n";
    std::cin >> std::setw(10) >> buf2;
    std::cout << buf2;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
