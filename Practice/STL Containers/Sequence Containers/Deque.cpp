/*
 * std::dequeue
 *  - SYNTAX:
 *      template<
 *          class T,
 *          class Container = std::deque<T>
 *      > class deque;
 * 
 *  - std::deque (double-ended queue) is an indexed sequence container that allows fast insertion
 *    and deletion at both its beginning and its end
 *  - as opposed to std::vector, the elements of a std::deque are not stored contiguously:
 *     - typical implementations use a sequence of individually allocated fixed-size arrays,
 *       with additional bookkeeping, which means indexed access to deque must perform two pointer
 *       dereferences, compared to vector's indexed access which performs only one
 *  - the storage of a deque is automatically expanded and contracted as needed
 *  - pros comparing to std::vector:
 *     - expansion of a deque is cheaper than the expansion of a std::vector because
 *       it does not involve copying of the existing elements to a new memory location
 *  - cons comparing to std::vector:
 *     - typically has large minimal memory cost
 * 
 *  - time complexity:
 *     - Random access - constant O(1)
 *     - Insertion or removal of elements at the end or beginning - constant O(1)
 *     - Insertion or removal of elements - linear O(n)
 *
 *  Other           Element access          Capacity            Modifiers
 *  - assign        - at                    - empty             - clear
 *                  - operator[]            - size              - insert
 *                  - front                 - max_size          - emplace
 *                  - back                  - shrink_to_fit     - erase
 *                                                              + push_back
 *                                                              - emplace_back
 *                                                              + pop_back
 *                                                              + push_front
 *                                                              - emplace_front
 *                                                              + pop_front
 *                                                              - resize
 *                                                              - swap
 */

#include <iostream>
#include <deque>

void printDeque(const std::deque<int>& varDeq)
{
    for(int elem : varDeq)
        std::cout << elem << ' ';
    std::cout << '\n';
}

// std::deque functions
void initialization_and_assignment();
// Modifiers
void push_front_back();
void pop_front_back();

int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();

    // Modifiers
    push_front_back();
    pop_front_back();

    std::cout << "*****************************************************\n";
    return 0;
}

void initialization_and_assignment()
{
    /*
     * Initializations
     */
    std::deque<int> varDeq1 { 1, 2, 3, 4, 5 }; // 1) Uniform initialization
    std::cout << "Uniform initialization: ";
    printDeque(varDeq1);

    std::deque<int> varDeq2 = { 1, 2, 3, 4, 5 }; // 2) Initializer list
    std::cout << "Initializer list: ";
    printDeque(varDeq2);

    /*
     * - we can fill specified amount of deque elements with the same value
     * - value_of_elements can be omitted, and then the value is 0
     */
    std::deque<int> varDeq3(5, 1);
    std::cout << "Count values initialization 1: ";
    printDeque(varDeq3);
    
    std::deque<int> varDeq4(5);
    std::cout << "Count values initialization 2: ";
    printDeque(varDeq4);

    /*
     * Assignment 
     *  - it is possible to declare deque without initialization and afterwards
     *    assign values to deque using initializer list
     */
    std::deque<int> varDeq5;
    varDeq5 = {1, 2, 3, 4, 5 };
    std::cout << "Assignment after declaration: ";
    printDeque(varDeq5);

    std::cout << "------------------------------\n";
}

void push_front_back()
{
    std::deque<int> varDeq { 1, 2, 3, 4, 5 };
    std::cout << "Initial deque: ";
    printDeque(varDeq);

    varDeq.push_front(0);
    varDeq.push_back(6);
    std::cout << "Deque after pushing elements at front and back: ";
    printDeque(varDeq);

    std::cout << "------------------------------\n";
}

void pop_front_back()
{
    std::deque<int> varDeq { 1, 2, 3, 4, 5 };
    std::cout << "Initial deque: ";
    printDeque(varDeq);

    varDeq.pop_front();
    varDeq.pop_back();
    std::cout << "Deque after popping elements at front and back: ";
    printDeque(varDeq);

    std::cout << "------------------------------\n";
}