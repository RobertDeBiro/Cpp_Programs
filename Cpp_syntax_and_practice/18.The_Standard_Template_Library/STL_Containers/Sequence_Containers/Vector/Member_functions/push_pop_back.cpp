/*
 * push_back(const T& value) -> void
 * 
 * pop_back() -> void
 *
 * References:
 *  - https://en.cppreference.com/w/cpp/container/vector/push_back
 *  - https://en.cppreference.com/w/cpp/container/vector/pop_back
 * 
 */

#include <iostream>
#include <vector>

void printVector(const std::vector<int>& varVect)
{
    for(int elem : varVect)
        std::cout << elem << ' ';
    std::cout << '\n';
}

void printVectorSizeAndCapacity(const std::vector<int>& varVect)
{
    std::cout << "Size: " << varVect.size() << "   Capacity: " << varVect.capacity() << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> varVect { 1, 2, 3, 4, 5 };
    std::cout << "Initial vector: ";
    printVector(varVect);

    std::cout << "Push back: \n";
    varVect.push_back(6);
    printVector(varVect);
    std::cout << "Last value on the stack: " << varVect.back() << '\n';

    // We cannot extend vector just by assigning a value to element +1 from current last element
    printVectorSizeAndCapacity(varVect);
    varVect[6] = 7;
    printVectorSizeAndCapacity(varVect);
    printVector(varVect);

    std::cout << "Pop back: \n";
    varVect.pop_back();
    printVector(varVect);

    std::cout << "*****************************************************\n";
    return 0;
}
