/*
 * resize(size_type count) -> void
 *  - only size is changed, not the capacity
 *
 * References:
 *  - https://en.cppreference.com/w/cpp/container/vector/resize
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

    // By resizing vector only existing elements within new size are left, other are trimmed
    varVect.resize(2);
    std::cout << "Vector resized to a smaller value: ";
    printVector(varVect);
    printVectorSizeAndCapacity(varVect);

    std::cout << "*****************************************************\n";
    return 0;
}
