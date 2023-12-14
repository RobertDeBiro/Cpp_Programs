/*
 *  - if vector is already initialized and we want to change its values
 *    to one specific value, we can use 'assign()' function
 *  - it is very similar to syntax 'std::vector<int> varVect3(5, 1)'
 *    except this is used when vector is already initialized
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

    varVect.assign(5, 2);
    std::cout << "Assignment using assign: ";
    printVector(varVect);

    varVect.assign(3, 3);
    std::cout << "Assign only some elements: ";
    printVector(varVect);

    std::cout << "*****************************************************\n";
    return 0;
}
