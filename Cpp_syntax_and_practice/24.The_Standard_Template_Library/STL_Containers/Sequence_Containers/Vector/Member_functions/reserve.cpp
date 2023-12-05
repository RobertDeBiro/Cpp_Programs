/*
 * reserve(size_type new_capacity) -> void
 *  - compiler reserves more place then needed, i.e. capacity is most of the time
 *    bigger then actual vector size
 *  - compiler does that because resizing is expensive, so to decrease the number of
 *    resize operations (the amount of coppies)
 *  - if we know our vector will grow to some point, in order to optimize usage of vector
 *    we can use reserve() function
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/container/vector/reserve
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
    std::cout << "Size: " << varVect.size() << "  \tCapacity: " << varVect.capacity() << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> varVect;
    varVect.reserve(32);
    std::cout << "0. varVect: ";
    printVector(varVect);
    std::cout << "0. varVect, size and capacity: ";
    printVectorSizeAndCapacity(varVect);
    for(int i = 0; i < 32; ++i)
    {
        varVect.push_back(i);
        printVectorSizeAndCapacity(varVect);

        // We cannot assign the values in following way since reserve() doesn't allocate resources,
        // only decreases numbers of vector coppies
        //  - ERROR wouldn't appear, but vector values would be empty
        // varVect[i] = i;
    }

    // The moment size becomes bigger than capacity, capacity doubles
    varVect.push_back(33);
    printVectorSizeAndCapacity(varVect);

    // If we reserve smaller value of our capacity and size, nothing will be changed
    varVect.reserve(5);
    std::cout << "Reserving smaller size: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "*****************************************************\n";
    return 0;
}
