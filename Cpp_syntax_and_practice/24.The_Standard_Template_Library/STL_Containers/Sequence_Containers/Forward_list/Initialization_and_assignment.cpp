#include <iostream>
#include <forward_list>

void printFwdList(const std::forward_list<int>& varFwdList)
{
    for(int elem : varFwdList)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    /*
     * Initializations
     */
    std::forward_list<int> varFwdList1 { 1, 2, 3, 4, 5 }; // 1) Uniform initialization
    std::cout << "Uniform initialization: ";
    printFwdList(varFwdList1);

    std::forward_list<int> varFwdList2 = { 1, 2, 3, 4, 5 }; // 2) Initializer list
    std::cout << "Initializer list: ";
    printFwdList(varFwdList2);

    /*
     * - we can fill specified amount of forward_list elements with the same value
     * - value_of_elements can be omitted, and then the value is 0
     */
    std::forward_list<int> varFwdList3(5, 1);
    std::cout << "Count values initialization 1: ";
    printFwdList(varFwdList3);
    
    std::forward_list<int> varFwdList4(5);
    std::cout << "Count values initialization 2: ";
    printFwdList(varFwdList4);

    /*
     * Assignment 
     *  - it is possible to declare forward_list without initialization and afterwards
     *    assign values to forward_list using initializer list
     */
    std::forward_list<int> varFwdList5;
    varFwdList5 = {1, 2, 3, 4, 5 };
    std::cout << "Assignment after declaration: ";
    printFwdList(varFwdList5);

    // Following is not possible - fast random access with operator[] is not supported 
    //varFwdList5[0] = 2;

    std::cout << "*****************************************************\n";
    return 0;
}
