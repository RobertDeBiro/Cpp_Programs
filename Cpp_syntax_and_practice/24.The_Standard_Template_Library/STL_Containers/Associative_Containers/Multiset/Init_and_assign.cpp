#include <iostream>
#include <set>

template <typename T>
void printMultiset(T varSet)
{
    for(auto elem : varSet)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::multiset<int> varMultiset1{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "Initial set container: \n";
    printMultiset(varMultiset1);

    std::multiset<int, std::less<>> varMultiset2{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "std::less set container: \n";
    printMultiset(varMultiset2);

    std::multiset<int, std::greater<>> varMultiset3{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "std::greater set container: \n";
    printMultiset(varMultiset3);

    std::cout << "*****************************************************\n";
    return 0;
}
