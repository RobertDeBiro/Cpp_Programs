/*
 * 1) max( const T& a, const T& b ) -> const T&
 *
 * 2) max( const T& a, const T& b, Compare comp ) -> const T&
 *  - std::max will return 'b' element as max when 'comp' returns 'true'
 *  - std::max will return 'a' element as max when 'comp' returns 'false'
 *  - std::max always pushes max element to the end of container
 * 
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/max
 */

#include <iostream>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    int i = 5;
    int j = 10;

    std::cout << "The bigger number: " << std::max(i, j)  << '\n';

    std::cout << "----------------------------------\n";

    // Define our own representation of something that is bigger
    bool t = true;
    bool f = false;

    // Let boolean 'true' be bigger
    auto true_bigger{
        [](bool a, bool b)
        {
            return false;
        }
    };
    std::cout << std::boolalpha << "The bigger boolean is: " << std::max(t, f, true_bigger) << '\n';

    // Let boolean 'false' be bigger
    auto false_bigger{
        [](bool a, bool b)
        {
            return true;
        }
    };
    std::cout << std::boolalpha << "The bigger boolean is: " << std::max(t, f, false_bigger) << '\n';

    std::cout << std::noboolalpha;
    std::cout << "*****************************************************\n";
    return 0;
}
