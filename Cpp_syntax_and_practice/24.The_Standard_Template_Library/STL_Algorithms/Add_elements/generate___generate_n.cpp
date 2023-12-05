/*
 * std::generate(ForwardIt first, ForwardIt last, Generator g)
 *  - genereate will call "g" for every element from "first" to "last" and put inside container
 *    the return value of the generator
 *  - comparison with std::fill and std::iota:
 *     - std::fill - puts elements with the same specified value into container
 *     - std::generate - puts elements with generated values into container
 *     - std::iota - puts elements with contiguous values - starting from specified value - into container
 * 
 * std::generate_n(OutputIt first, Size count, Generator g)
 * 
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/generate
 *  - https://en.cppreference.com/w/cpp/algorithm/generate_n
 */

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> v(5);
    int i = 0;
    
    // ******************************* std::generate *******************************
    // Generate vector from begin to end, with following elements: 0 1 2 3 4
    std::generate(v.begin(), v.end(), [&]() { return i++; });
    std::cout << "Populating vector - define scope of vector: \n";
    for (const auto elem : v)
        std::cout << elem << ' ';
    std::cout << '\n';

    std::cout << "-------------------------------------\n";

    // ******************************* std::generate_n *******************************
    // Generates "n" amount of value starting from specified container element
    std::generate_n(std::back_inserter(v), 5, [&]() { return i++; });
    std::cout << "Populating vector - define number of elements: \n";
    for (const auto elem : v)
        std::cout << elem << ' ';
    std::cout << '\n';

    // Enter every element from terminal
    auto gen = [&]() { int x;
                       std::cout << "Enter x: ";
                       std::cin >> x;
                       return x; };
    std::generate_n(std::back_inserter(v), 5, gen);
    std::cout << "Populating vector - define number of elements: \n";
    for (const auto elem : v)
        std::cout << elem << ' ';
    std::cout << '\n';
    
    // When using generate_n in following way, it is actually the same as function std::fill_n,
    // except here callable object is used
    std::generate_n(v.begin(), 2, [&]() { return 100; });
    std::cout << "Updating vector: \n";
    for (const auto elem : v)
        std::cout << elem << ' ';
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}