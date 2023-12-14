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
    std::cout << "0. varVect: ";
    printVector(varVect);
    std::cout << "0. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "-------------------------------------\n";

    //* Insert element, which doubles capacity
    auto it = varVect.insert(varVect.begin(), 200);
    std::cout << "1. varVect: ";
    printVector(varVect);
    std::cout << "1. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);
    std::cout << "Inserted value (iterator value) = " << *it << '\n';

    std::cout << "-------------------------------------\n";

    //* Shrink capacity to the size of the vector
    varVect.shrink_to_fit();
    std::cout << "2. varVect: ";
    printVector(varVect);
    std::cout << "2. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "-------------------------------------\n";

    //* Print value pointed by previously collected vector iterator
    //  - when reallocation occurs, all iterators, including the past the end iterator,
    //    and all references to the elements are invalidated
    //  - iterator value will be undefined
    std::cout << "Iterator value = " << *it << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
