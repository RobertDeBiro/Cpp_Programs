/*
 * std::fill(ForwardIt first, ForwardIt last, const T& value) -> void
 *  - comparison with std::generate and std::iota:
 *     - std::fill - puts elements with the same specified value into container
 *     - std::generate - puts elements with generated values into container
 *     - std::iota - puts elements with contiguous values - starting from specified value - into container
 *
 * std::fill_n(OutputIt first, Size count, const T& value) -> void
 * 
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/fill
 *  - https://en.cppreference.com/w/cpp/algorithm/fill_n
 */

#include <algorithm>
#include <vector>
#include <iostream>
 
int main()
{
    std::cout << "*****************************************************\n";
    
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << "Initial vector: ";
    for (auto elem : v)
        std::cout << elem << " ";
    std::cout << "\n";
 
    // ******************************* std::fill *******************************
    // Fill from v.begin() to v.begin() + 3, with number "-1"
    //  - because second iterator is considered as "last", compiler reads it as it reads v.end(),
    //    so the last address that it reads is not v.begin() + 3, but rather v.begin() + 2
    std::fill(v.begin(), v.begin() + 3, -1);
 
    std::cout << "Vector after filling: ";
    for (auto elem : v)
        std::cout << elem << " ";
    std::cout << "\n";

    // ERROR: we cannot fill elements into non-existing part of the vector
    // std::fill(v.end(), v.end() + 2, -1);

    std::cout << "-----------------------------------------------------------\n";

    // ******************************* std::fill_n *******************************
    // Starting from v.begin() + 4, fill "3" times, number "-2"
    std::fill_n(v.begin() + 4, 3, -2);
    
    std::cout << "Vector after filling, using std::fill_n: ";
    for (auto elem : v)
        std::cout << elem << " ";
    std::cout << "\n";

    std::cout << "*****************************************************\n";
    return 0;
}