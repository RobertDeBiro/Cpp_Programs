/*
 * std::stack
 *  - SYNTAX:
 *      template<
 *          class T,
 *          class Container = std::deque<T>
 *      > class queue;
 * 
 *  - std::stack class is a container adapter that gives the programmer the functionality of 
 *    a stack - specifically, a LIFO (last-in, first-out) data structure
 *  - the class template acts as a wrapper to the underlying container
 *     - in other words, std::stack is implemented as some other container
 *     - by default it is implemented internally as std::deque (we can see that also in SYNTAX)
 *
 *  Element access          Capacity            Modifiers
 *  + top                   + empty             + push
 *                          - size              - emplace
 *                                              + pop
 *                                              - swap
 */

#include <iostream>
#include <stack>
#include <vector>

// Printing stack is specific since we can access only the top element
//  - therefore, after printing that top element that we can access, we need to pop it out
//  - elements are popped out in the opposite direction from std::queue
void printStack(std::stack<int> varStk)
{
    int i = 1;
    while(!varStk.empty())
    {
        std::cout << varStk.top() << " (" << i << ". element popped) \n";
        varStk.pop();
        ++i;
    }
    std::cout << '\n';
}

void printStack(std::stack<int, std::vector<int>> varStk)
{
    int i = 1;
    while(!varStk.empty())
    {
        std::cout << varStk.top() << " (" << i << ". element popped) \n";
        varStk.pop();
        ++i;
    }
    std::cout << '\n';
}

// std::stack functions
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
    std::stack<int> varStk1;
    varStk1.push(1);
    varStk1.push(2);
    varStk1.push(3);
    std::cout << "Printing queue: \n";
    printStack(varStk1);

    // If using std::vector as an internal container, rather then std::deque,
    // are printout will be the same, but internal managament of the stack is not the same
    std::stack<int> varStk2;
    varStk2.push(1);
    varStk2.push(2);
    varStk2.push(3);
    std::cout << "Printing queue which internally uses std::vector: \n";
    printStack(varStk2);

    std::cout << "------------------------------\n";
}

