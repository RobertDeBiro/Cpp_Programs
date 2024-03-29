#include <iostream>
#include <vector>

void printVector(const std::vector<int>& varVect)
{
    for(int elem : varVect)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> varVect { 1, 2, 3, 4, 5, 6 };
    std::cout << "0. varVect: ";
    printVector(varVect);

    //* Erase only one element
    varVect.erase(varVect.begin());
    std::cout << "1. varVect: ";
    printVector(varVect);

    //* Erase scope of elements
    //  - erase 2. and 3. element
    varVect.erase(varVect.begin() + 1, varVect.begin() + 3);
    std::cout << "2. varVect: ";
    printVector(varVect);

    //* Erase element with required value
    //  - erase element with value '2'
    //  - after erase of iterator, some compilers will lost info about iterator,
    //    hence we won't be able to use it anymore (e.g. my VS compiler)
    //  - in this compiler, everything is fine!
    for (auto it = begin(varVect); it != end(varVect); it++)
    {
        if (*it == 2)
        {
            std::cout << "Iterator value before erase = " << *it << '\n';
            varVect.erase(it);
            std::cout << "Iterator value after erase = " << *it << '\n';
        }
    }
    std::cout << "3. varVect: ";
    printVector(varVect);

    std::cout << "*****************************************************\n";
    return 0;
}
