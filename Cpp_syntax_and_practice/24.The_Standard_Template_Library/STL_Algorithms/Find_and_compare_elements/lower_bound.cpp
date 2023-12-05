/*
 * lower_bound( ForwardIt first, ForwardIt last, const T& value ) -> ForwardIt
 *
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/lower_bound
 */

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    const std::vector<int> data = {1, 2, 4, 5, 5, 6};

    std::cout << "Enter value for testing lower bound: ";
    int i;
    std::cin >> i;

    auto lower = std::lower_bound(data.begin(), data.end(), i);
    if (lower != data.end())
    {
        std::cout << "First element in vector that is greater or equal than " << i << " is "
                  << *lower << '\n';
    }
    else
    {
        std::cout << "Neither of vector elements is greater or equal than " << i << '\n';
    }
    
    std::cout << "*****************************************************\n";
    return 0;
}