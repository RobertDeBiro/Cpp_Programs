/*
 * References:
 *  - https://en.cppreference.com/w/cpp/container/vector/size
 *  - https://en.cppreference.com/w/cpp/container/vector/capacity
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

    // Reducing length to 3, whereas capacity remains the same
    //  - once set, capacity can't be shrinked!
    varVect = {1, 2, 3};
    std::cout << "1. varVect: ";
    printVector(varVect);
    std::cout << "1. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // Increase both length and capacity to amount of 7
    // - when increasing vector by using assignment, capacity
    //   is increased to the size of the vector
    varVect = {1, 2, 3, 4, 5, 6, 7};
    std::cout << "2. varVect: ";
    printVector(varVect);
    std::cout << "2. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // With push_back we are adding one element and increasing vector size
    //  - when increasing a vector by using push_back() capacity doubles its
    //    value in order to avoid a lot of coppies
    varVect.push_back(8);
    std::cout << "3. varVect: ";
    printVector(varVect);
    std::cout << "3. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // With pop_back we are removing one element and decreasing vector size
    varVect.pop_back();
    std::cout << "4. varVect: ";
    printVector(varVect);
    std::cout << "4. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // Vector can be size of 0 when in same time having some capacity
    varVect.clear();
    std::cout << "5. varVect: ";
    printVector(varVect);
    std::cout << "5. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // Reseting capacity to amount of size
    varVect.shrink_to_fit();
    std::cout << "6. varVect: ";
    printVector(varVect);
    std::cout << "6. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "*****************************************************\n";
    return 0;
}
