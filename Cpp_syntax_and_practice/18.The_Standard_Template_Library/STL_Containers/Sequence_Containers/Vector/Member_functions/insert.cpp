/*
 * 1) insert(iterator pos, const T& value) -> iterator
 *      - insert value before pos
 *      - return value is iterator pointing to the inserted element
 *      - example:
 *          - insert 200 at the beginning of the vector
 *          - after inserting element, first element becomes second
 *            and new element is inserted in front of him
 * 
 * 2) insert(const_iterator pos, size_type count, const T& value) -> iterator
 * 
 * 3) insert(iterator pos, InputIt first, InputIt last) -> void
 *      - inserts elements from range [first, last) before pos
 *      - examples:
 *          - insert everything contained inside vect2 to vect1, starting from index 2
 *          - insert array at the beginning of the vector
 *          - insert array at the end of the vector
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/container/vector/insert
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
    std::cout << "0. varVect: ";
    printVector(varVect);
    std::cout << "0. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // Insert 200 at the beginning of the vector
    //  - when inserting an element to a vector, capacity will increase its value by double,
    //    in order to avoid expensive vector coppies (the same as with push_back())
    auto it = varVect.insert(varVect.begin(), 200);
    std::cout << "1. varVect: ";
    printVector(varVect);
    std::cout << "1. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // Insert 300, 2 times, in first 2 positions of the vector
    varVect.insert(it, 2, 300); 
    std::cout << "2. varVect: ";
    printVector(varVect);
    std::cout << "2. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // Insert everything contained inside additional vector "vect2", starting from index 2
    std::vector<int> vect2(2, 400);
    varVect.insert(std::next(varVect.begin(), 2), vect2.begin(), vect2.end());
    std::cout << "3. varVect: ";
    printVector(varVect);
    std::cout << "3. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // Insert array at the beginning of the vector
    int arr[] = { 501,502,503 };
    varVect.insert(varVect.begin(), arr, arr + std::size(arr));
    std::cout << "4. varVect: ";
    printVector(varVect);
    std::cout << "4. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // Insert array at the end of the vector
    varVect.insert(varVect.end(), { 601,602,603 } );
    std::cout << "5. varVect: ";
    printVector(varVect);
    std::cout << "5. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "*****************************************************\n";
    return 0;
}
