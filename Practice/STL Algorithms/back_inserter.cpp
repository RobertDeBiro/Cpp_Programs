#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    /*
     * std::back_inserter(Container& c) -> std::back_insert_iterator<Container>
     *  - returns an iterator which can be used to add elements to the end of the container c
     *  - mostly used as an input parameter to other algorithms, such as:
     *    std::fill_n, std::generate_n
     *  - example:
     *     - adding number -1, 3 times, at the back of the vector
     */
    std::fill_n(std::back_inserter(v), 3, -1);
    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}