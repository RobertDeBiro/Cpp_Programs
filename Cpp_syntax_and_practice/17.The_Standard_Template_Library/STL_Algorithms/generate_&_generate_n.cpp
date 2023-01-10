#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> v(5);
    int i = 0;
    
    // ******************************* std::generate *******************************
    /*
     * std::generate(ForwardIt first, ForwardIt last, callable object)
     *  - generate values returned by callable object into specified container scope
     *  - comparison with std::fill and std::iota:
     *     - std::fill - puts elements with the same specified value into container
     *     - std::generate - puts elements with generated values into container
     *     - std::iota - puts elements with contiguous values - starting from specified value - into container
     *  - example:
     *     - generate vector with following 5 elements: 0, 1, 2, 3, 4
     */
    std::generate(v.begin(), v.end(), [&]() { return i++; });
    std::cout << "***** Populating vector - define scope of vector *****\n";
    for (const auto elem : v)
        std::cout << elem << '\n';

    // ******************************* std::generate_n *******************************
    /*
     * std::generate_n(OutputIt first, Size count, callable object)
     *  - generates "n" amount of value starting from specified container element
     */
    std::generate_n(std::back_inserter(v), 5, [&]() { return i++; });
    std::cout << "***** Populating vector - define number of elements *****\n";
    for (const auto elem : v)
        std::cout << elem << '\n';
    
    // When using generate_n in following way, it is actually the same as function std::fill_n,
    // except here callable object is used
    std::generate_n(v.begin(), 2, [&]() { return 100; });
    std::cout << "***** Updating vector *****\n";
    for (const auto elem : v)
        std::cout << elem << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}