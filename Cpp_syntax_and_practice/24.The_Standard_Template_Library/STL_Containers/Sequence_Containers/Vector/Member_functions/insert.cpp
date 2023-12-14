//* Insert is basically the same as push_back, except it contains some additional features

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

    std::cout << "------------------------------------------------------------------\n";

    //* Insert element at the beginning of the vector
    //  - when inserting an element to a vector, capacity will increase its value by double,
    //    in order to avoid expensive vector coppies (the same as with 'push_back()')
    auto it = varVect.insert(varVect.begin(), 200);
    std::cout << "1. varVect: ";
    printVector(varVect);
    std::cout << "1. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------------------------------------------\n";

    //* Insert element multiple times, at the beginning of the vector
    varVect.insert(it, 2, 300); 
    std::cout << "2. varVect: ";
    printVector(varVect);
    std::cout << "2. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------------------------------------------\n";

    //* Insert vector at index '2'
    std::vector<int> vect2(2, 400);
    varVect.insert(std::next(varVect.begin(), 2), vect2.begin(), vect2.end());
    std::cout << "3. varVect: ";
    printVector(varVect);
    std::cout << "3. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------------------------------------------\n";

    //* Insert array at the beginning of the vector
    int arr[] = { 501,502,503 };
    varVect.insert(varVect.begin(), arr, arr + std::size(arr));
    std::cout << "4. varVect: ";
    printVector(varVect);
    std::cout << "4. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------------------------------------------\n";

    //* Insert array literal at the end of the vector
    varVect.insert(varVect.end(), { 601,602,603 } );
    std::cout << "5. varVect: ";
    printVector(varVect);
    std::cout << "5. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "*****************************************************\n";
    return 0;
}
