/*
 * C++ Primer
 * Exercise Section 3.4.1
 *  - Exercise 3.23
 */

#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int>& varVect)
{
    for(auto it = varVect.begin(); it != varVect.end(); it++)
        std::cout << *it << ' ' ;
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::cout << "Initial vector: ";
    printVector(v);

    std::cout << "-----------------------------------------------";

    // Double the elements values
    for(auto it = v.begin(); it != v.end(); it++)
    {
        *it = *it * 2;
    }
    std::cout << '\n';

    std::cout << "Updated vector: ";
    printVector(v);

    std::cout << "*****************************************************\n";
    return 0;
}