/*
 * std::queue
 *  - SYNTAX:
 *      template<
 *          class T,
 *          class Container = std::deque<T>
 *      > class queue;
 * 
 *  - std::queue class is a container adapter that gives the programmer the functionality of 
 *    a queue - specifically, a FIFO (first-in, first-out) data structure
 *  - the class template acts as a wrapper to the underlying container
 *     - in other words, std::stack is implemented as some other container
 *     - by default it is implemented internally as std::deque
 *
 *  Element access          Capacity            Modifiers
 *  + front                 + empty             + push
 *  - back                  - size              - emplace
 *                                              + pop
 *                                              - swap
 */

#include <iostream>
#include <queue>

// Printing queue is specific since we can access only the first element
//  - therefore, after printing that first we can access, we need to pop it out
void printQueue(std::queue<int> varQue)
{
    int i = 1;
    while(!varQue.empty())
    {
        std::cout << varQue.front() << " (" << i << ". element popped) \n";
        varQue.pop();
        ++i;
    }
    std::cout << '\n';
}

// std::queue functions
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
     * We cannot initialized/assigned queue in either of following ways
     *  - that is because que can have only one value inserted at a time
     *    not several of them as we tried to do
     *  - there is an example with varQue4 where we tried to add only one element
     *    but since we are using initialization list, queue still doesn't allow it
     *  - only way to add only one element at a time is by using push() function
     */
    // std::queue<int> varQue1{ 1, 2, 3 };
    // std::queue<int> varQue2 = { 1, 2, 3 };
    // std::queue<int> varQue3;
    // varQue3 = { 1, 2, 3 };
    // std::queue<int> varQue4{ 1 };

    std::queue<int> varQue;
    varQue.push(1);
    varQue.push(2);
    varQue.push(3);
    std::cout << "Printing queue: \n";
    printQueue(varQue);

    std::cout << "------------------------------\n";
}