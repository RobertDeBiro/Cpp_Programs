#include <iostream>
#include <array>
#include <numeric> // iota

int main()
{
    std::cout << "*****************************************************\n";

    std::array<int, 5> arr{};
    for(const auto elem : arr)
        std::cout << elem << ' ';
    std::cout << '\n';

    /*
     * std::iota(InputIt first, InputIt last, T value) -> void
     *  - inputs inside container a contiguous series of values starting from the "value"
     *  - comparison with std::fill and std::generate:
     *     - std::fill - puts elements with the same specified value into container
     *     - std::generate - puts elements with generated values into container
     *     - std::iota - puts elements with contiguous values - starting from specified value - into container
     */
    std::iota(arr.begin(), arr.end(), 10);
    for(const auto elem : arr)
        std::cout << elem << ' ';
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
