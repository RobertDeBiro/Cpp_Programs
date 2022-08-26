#include <iostream>
#include <array>
#include <numeric>

int main()
{
    std::cout << "*****************************************************\n";

    std::array arr{ 1, 2, 3, 4, 5 };

    /*
     * template< class InputIt, class T> - class doesn't present class, but rather keyword for template type
     *                                   - we could also write typename
     * std::accumulate(InputIt first, InputIt last, T init) -> T
     *  - comparison to std::reduce
     *     - std::accumulate - sums elements starting from the initial value
     *     - std::reduce - sums the elements
     */
    int sum1{ std::accumulate(arr.begin(), arr.end(), 0) };
    std::cout << "Accumulated numbers from array = " << sum1 << '\n';

    int sum2{ std::accumulate(arr.begin(), arr.end(), 10) };
    std::cout << "Accumulated numbers from array + init integer = " << sum2 << '\n';

    // Initial value type must be the same as container element type!
    int sum3{ std::accumulate(arr.begin(), arr.end(), 20.5) };
    std::cout << "Accumulated numbers from array + init double = " << sum3 << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
