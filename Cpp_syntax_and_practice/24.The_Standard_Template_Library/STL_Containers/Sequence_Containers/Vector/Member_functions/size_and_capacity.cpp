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
    std::cout << "Size: " << varVect.size() << "\tCapacity: " << varVect.capacity() << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> varVect { 1, 2, 3, 4, 5 };
    std::cout << "0. varVect: ";
    printVector(varVect);
    std::cout << "0. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------------\n";

    //* Assign smaller amount of elements to vector
    // - size (length) is reduced, capacity remains the same
    // - once set, capacity can't be shrinked! (except with 'shrink_to_fit()' method)
    varVect = {1, 2, 3};
    std::cout << "1. varVect: ";
    printVector(varVect);
    std::cout << "1. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------------\n";

    //* Assign bigger amount of elements to vector
    // - both length and capacity will increase
    // - capacity is increased to the size of the vector (won't be doubled)
    varVect = {1, 2, 3, 4, 5, 6, 7};
    std::cout << "2. varVect: ";
    printVector(varVect);
    std::cout << "2. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------------\n";

    //* Add element with 'push_back()'
    // - lenght is increased by one, capacity doubles its value in order to avoid a lot of coppies
    varVect.push_back(8);
    std::cout << "3. varVect: ";
    printVector(varVect);
    std::cout << "3. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------------\n";

    //* Remove element with 'pop_back()'
    // - length is decreased by one, capacity remains the same
    varVect.pop_back();
    std::cout << "4. varVect: ";
    printVector(varVect);
    std::cout << "4. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------------\n";

    //* Clear vector using 'clear()'
    // - length decreases to '0', capacity remains the same
    varVect.clear();
    std::cout << "5. varVect: ";
    printVector(varVect);
    std::cout << "5. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------------\n";

    //* Reset capacity to amount of size
    varVect.shrink_to_fit();
    std::cout << "6. varVect: ";
    printVector(varVect);
    std::cout << "6. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "*****************************************************\n";
    return 0;
}
