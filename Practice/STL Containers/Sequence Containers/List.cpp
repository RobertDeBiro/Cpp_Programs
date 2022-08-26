/*
 * std::list
 *  - SYNTAX:
 *      template<
 *          class T,
 *          class Allocator = std::allocator<T>
 *      > class list;
 * 
 *  - std::list is a sequence container that supports constant time
 *    insertion and removal of elements from anywhere in the container
 *  - fast random access is not supported (element is accessed with O(n))
 *  - it is implemented as a doubly-linked list
 * 
 *  Other           Element access          Capacity            Modifiers           Operations
 *  - assign        - front                 - empty             - clear             + merge
 *                  - back                  - size              - insert            + splice
 *                                          - max_size          - emplace           - remove, remove_if
 *                                                              - erase             - reverse
 *                                                              - push_back         + unique
 *                                                              - emplace_back      + sort
 *                                                              - pop_back
 *                                                              - push_front
 *                                                              - emplace_front
 *                                                              - pop_front
 *                                                              - resize
 *                                                              - swap
 */

#include<iostream>
#include<list>

void printList(const std::list<int>& varList)
{
    for(int elem : varList)
        std::cout << elem << ' ';
    std::cout << '\n';
}

// std::list functions
void initialization_and_assignment();
// Operations
void merge();
void splice();
void unique();
void sort();

int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();

    // Operations
    merge();
    splice();
    unique();
    sort();

    std::cout << "*****************************************************\n";
    return 0;
}

void initialization_and_assignment()
{
    /*
     * Initializations
     */
    std::list<int> varList1 { 1, 2, 3, 4, 5 }; // 1) Uniform initialization
    std::cout << "Uniform initialization: ";
    printList(varList1);

    std::list<int> varList2 = { 1, 2, 3, 4, 5 }; // 2) Initializer list
    std::cout << "Initializer list: ";
    printList(varList2);

    /*
     * - we can fill specified amount of list elements with the same value
     * - value_of_elements can be omitted, and then the value is 0
     */
    std::list<int> varList3(5, 1);
    std::cout << "Count values initialization 1: ";
    printList(varList3);
    
    std::list<int> varList4(5);
    std::cout << "Count values initialization 2: ";
    printList(varList4);

    /*
     * Assignment 
     *  - it is possible to declare list without initialization and afterwards
     *    assign values to list using initializer list
     */
    std::list<int> varList5;
    varList5 = {1, 2, 3, 4, 5 };
    std::cout << "Assignment after declaration: ";
    printList(varList5);

    /*
     * We can create list of list by using one of the following syntaxes:
     *  1) std::list<std::list<int>> varList
     *  2) std::list<int> varList[3]
     */
    std::list<int> varList6[3];
    for (int i = 0; i < 3; i++)
    {
        varList6[i] = {1 + i, 2 + i, 3 + i};
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << i + 1 << ". list of the list: ";
        printList(varList6[i]);
    }

    std::cout << "------------------------------\n";
}

void merge()
{
    std::list<int> varList1 { 1, 2, 3, 4, 5 };
    std::cout << "List1: ";
    printList(varList1);

    std::list<int> varList2 { 6, 7, 8, 9, 10 };
    std::cout << "List2: ";
    printList(varList2);

    varList1.merge(varList2);
    std::cout << "List2 merged to List1: ";
    printList(varList1);

    std::cout << "------------------------------\n";
}

void splice()
{
    std::list<int> varList1 { 1, 2, 3, 4, 5 };
    std::cout << "List1: ";
    printList(varList1);

    std::list<int> varList2 { 6, 7, 8, 9, 10 };
    std::cout << "List2: ";
    printList(varList2);

    /*
     * splice( const_iterator pos, list& other) -> void
     *  - transfers elements from one list to another
     *  - in this example, elements from varList2 are transfered to the position
     *    of the varList1.begin() i.e. to the beginning of the varList1
     *  - after transfering there are no elements inside list from which elements are transfered
     */
    varList1.splice(varList1.begin(), varList2);
    std::cout << "List2 spliced to the beginning of the List1: ";
    printList(varList1);
    std::cout << "List2 after splicing is empty: ";
    printList(varList2);

    std::list<int> varList3 { 100, 200, 300, 400 };
    std::cout << "List3: ";
    printList(varList3);

    std::list<int> varList4 { 220, 280 };
    std::cout << "List4: ";
    printList(varList4);
    
    varList3.splice(std::next(varList3.begin(), 2), varList4);
    std::cout << "List4 spliced to the middle of the List3: ";
    printList(varList3);

    std::cout << "------------------------------\n";
}

void unique()
{
    std::list<int> varList { 1, 2, 3, 2, 4, 4, 5, 5, 1 };
    std::cout << "Initial list: ";
    printList(varList);

    // unique() only removes adjacent duplicates
    varList.unique();
    std::cout << "List after removing adjacent duplicates: ";
    printList(varList);

    std::cout << "------------------------------\n";
}

void sort()
{
    std::list<int> varList { 3, 1, 5, 4, 2 };
    std::cout << "Initial list: ";
    printList(varList);

    varList.sort();
    std::cout << "Sorted list: ";
    printList(varList);

    std::cout << "------------------------------\n";
}