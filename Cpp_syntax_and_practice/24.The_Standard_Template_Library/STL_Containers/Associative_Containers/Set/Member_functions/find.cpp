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
    std::cout << "Initial set container: ";
    printSet(varSet);

    auto it = varSet.find(8);
    if (it != varSet.end())
        std::cout << "Element " << *it << " found!\n";

    std::cout << "*****************************************************\n";
    return 0;
}
