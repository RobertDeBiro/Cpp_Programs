/*
 * at(size_type pos) -> reference
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/container/vector/at
 *  - https://en.cppreference.com/w/cpp/container/vector/operator_at
 */

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

    std::vector<int> varVect { 1, 2, 3, 4, 5 };
    std::cout << "Initial vector: ";
    printVector(varVect);

    /*
     * We can fetch element in 2 ways:
     *  1) [index]
     *  2) .at(index)
     */
    std::cout << "Fetching element using []: " << varVect[1]
              << " and .at(): " << varVect.at(3) << '\n';

    try
    {
        varVect.at(8) = 10;
    }
    catch(const std::out_of_range& e)
    {
        std::cout << "Exception \"out_of_range\" is thrown!: ";
        std::cerr << e.what() << '\n';
    }

    std::cout << "*****************************************************\n";
    return 0;
}
