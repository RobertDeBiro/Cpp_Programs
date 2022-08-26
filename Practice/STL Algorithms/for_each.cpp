#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    std::cout << "*****************************************************\n";

    std::vector nums{ 1, 2, 3, 4 };

    /*
     * std::for_each(InputIt first, InputIt last, callable object) -> callable object
     *  - executes callable object on every element of the container and returns the callable object
     */
    auto callObj = std::for_each(begin(nums), end(nums),
                                 [](int element) { std::cout << "Number: " << element << '\n'; });
    std::cout << "Callable object after returning: ";
    callObj(5);

    std::cout << "*****************************************************\n";
    return 0;
}
