/*
 * 1) min( const T& a, const T& b ) -> const T&
 *
 * 2) min( const T& a, const T& b, Compare comp ) -> const T&
 *  - std::min will return 'b' element as min when 'comp' returns 'true'
 *  - std::min will return 'a' element as min when 'comp' returns 'false'
 *  - std::min always pushes min element to the end of container
 * 
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/min
 */

#include <iostream>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    int i = 5;
    int j = 10;

    std::cout << "The smaller number: " << std::min(i, j)  << '\n';

    std::cout << "----------------------------------\n";

    // Define our own representation of something that is smaller
    bool t = true;
    bool f = false;

    // Let boolean 'true' be smaller
    auto true_smaller{
        [](bool a, bool b)
        {
            return false;
        }
    };
    std::cout << std::boolalpha << "The smaller boolean is: " << std::min(t, f, true_smaller) << '\n';

    // Let boolean 'false' be smaller
    auto false_smaller{
        [](bool a, bool b)
        {
            return true;
        }
    };
    std::cout << std::boolalpha << "The smaller boolean is: " << std::min(t, f, false_smaller) << '\n';

    std::cout << std::noboolalpha;
    std::cout << "*****************************************************\n";
    return 0;
}