/*
 * C++ Primer
 * Exercise Section 3.4.1
 *  - Exercise 3.21
 */

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void printVectorElemSize_It(const T& varVect)
{
    std::cout << "Vector elements: ";
    for(auto it = varVect.begin(); it != varVect.end(); it++)
        std::cout << *it << ' ';
    std::cout << '\n';
    std::cout << "Vector size: " << varVect.size() << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    // Vector elem: /
    // Vector size: 0
    vector<int> v1;
    printVectorElemSize_It(v1);

    std::cout << "---------------------------------------------\n";

    // Vector elem: 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    // Vector size: 10
    vector<int> v2(10);
    printVectorElemSize_It(v2);

    std::cout << "---------------------------------------------\n";

    // Vector elem: 42, 42, 42, 42, 42, 42, 42, 42, 42, 42
    // Vector size: 10
    vector<int> v3(10, 42);
    printVectorElemSize_It(v3);

    std::cout << "---------------------------------------------\n";

    // Vector elem: 10
    // Vector size: 1
    vector<int> v4{ 10 };
    printVectorElemSize_It(v4);

    std::cout << "---------------------------------------------\n";

    // Vector elem: 10, 42
    // Vector size: 2
    vector<int> v5{ 10, 42 };
    printVectorElemSize_It(v5);

    std::cout << "---------------------------------------------\n";

    // Vector elem: ""
    // Vector size: 10
    //  - if our data type cannot add value inside curly braces (string cannot receive 10)
    //    curly braces will function as we are having parenthesis, i.e. it will initialize
    //    amount of 10 string elements
    vector<string> v6{ 10 };
    printVectorElemSize_It(v6);

    std::cout << "---------------------------------------------\n";

    // Vector elem: hi, hi, hi, hi, hi, hi, hi, hi, hi, hi
    // Vector size: 10
    vector<string> v7{ 10, "hi" };
    printVectorElemSize_It(v7);

    std::cout << "*****************************************************\n";
    return 0;
}