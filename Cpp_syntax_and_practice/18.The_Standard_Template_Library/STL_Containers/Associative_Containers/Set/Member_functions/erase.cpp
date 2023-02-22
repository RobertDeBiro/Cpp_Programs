/*
 * erase( iterator pos ) -> iterator
 *
 * References:
 *  - https://en.cppreference.com/w/cpp/container/set/erase
 */

#include <iostream>
#include <set>

template <typename T>
void printSet(T varSet)
{
    for(auto elem : varSet)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::set<int> varSet{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "Initial set container: \n";
    printSet(varSet);

    varSet.erase(std::next(varSet.begin(), 2));
    std::cout << "Container after erasing an element: \n";
    printSet(varSet);

    std::cout << "*****************************************************\n";
    return 0;
}
