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
    auto it = varVect.begin();
    std::cout << "Iterator and pointed value: " << *it << '\n';

    std::cout << "-------------------------------------\n";

    //* Push element on the vector
    std::cout << "Push back: \n";
    varVect.push_back(6);
    printVector(varVect);
    // When vector increases it is fully coppied to a new memory location, hence
    // iterator 'it' will also change
    std::cout << "Iterator and pointed value after push_back: " << *it << '\n';

    std::cout << "-------------------------------------\n";

    //* Read last (top) vector element
    std::cout << "Last value on the stack: " << varVect.back() << '\n';

    std::cout << "-------------------------------------\n";

    //* Assign new vector element
    //  - we cannot extend vector just by assigning a value to element +1 from current last element!
    printVectorSizeAndCapacity(varVect);
    varVect[6] = 7;
    printVectorSizeAndCapacity(varVect);
    printVector(varVect);

    std::cout << "-------------------------------------\n";

    //* Pop element from the vector
    std::cout << "Pop back: \n";
    varVect.pop_back();
    printVector(varVect);

    std::cout << "*****************************************************\n";
    return 0;
}
