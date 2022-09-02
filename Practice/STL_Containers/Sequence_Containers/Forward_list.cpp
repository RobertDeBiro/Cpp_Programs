/*
 * std::forward_list
 *  - SYNTAX:
 *      template<
 *          class T,
 *          class Allocator = std::allocator<T>
 *      > class forward_list;
 * 
 *  - std::forward_list is a sequence container that supports fast
 *    insertion and removal of elements from anywhere in the container
 *  - fast random access is not supported (element is accessed with O(n))
 *  - it is implemented as a singly-linked list
 * 
 *  Other           Element access          Capacity            Modifiers           Operations
 *  - assign        - front                 - empty             - clear             - merge
 *                                          - max_size          - insert_after      - splice_after
 *                                                              - emplace_after     - remove, remove_if
 *                                                              - erase_after       - reverse
 *                                                              - push_front        - unique
 *                                                              - emplace_front     - sort
 *                                                              - pop_front
 *                                                              - resize
 *                                                              - swap
 * TODO 3:23/12:38
 */

#include <iostream>
#include <forward_list>

void printFwdList(const std::forward_list<int>& varFwdList)
{
    for(int elem : varFwdList)
        std::cout << elem << ' ';
    std::cout << '\n';
}

// std::forward_list functions
void initialization_and_assignment();

int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();

    std::cout << "*****************************************************\n";
    return 0;
}

void initialization_and_assignment()
{
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

    std::cout << "------------------------------\n";
}