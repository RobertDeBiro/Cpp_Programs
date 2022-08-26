/*
 * std::array
 *  - SYNTAX:
 *      template<
 *          class T, 
 *          std::size_t N
 *      > struct array;
 * 
 *  - std::array is a sequence container that encapsulates fixed size array
 *  - this container is an aggregate type with the same semantics as a struct
 *    holding a C-style array T[N] as its only non-static data member
 *  - unlike a C-style array, it doesn't decay to T* automatically
 *
 *  - time complexity:
 *     - Random access - constant O(1)
 * 
 *  Element access          Capacity            Operations
 *  + at                    - empty             + fill
 *  + operator[]            + size              - swap
 *  + front                 - max_size
 *  + back
 *  - data
 */

#include <iostream>
#include <array>

// std::array won't decay when sending into a function by value
void printArray(const std::array<int, 5>& varArr)
{
    for(int elem : varArr)
        std::cout << elem << ' ';
    std::cout << '\n';
}

void initialization_and_assignment();
// Element access
void at_and_operator();
void front_and_back();
// Operations
void fill();


int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();

    // Element access
    at_and_operator();
    front_and_back();

    // Operations
    fill();

    std::cout << "*****************************************************\n";
    return 0;
}

void initialization_and_assignment()
{
    /*
     * Initializations
     */
    std::array<int, 5> varArr1 { 1, 2, 3, 4, 5 }; // 1) Uniform initialization
    std::cout << "Uniform initialization: ";
    printArray(varArr1);

    std::array<int, 5> varArr2 = { 1, 2, 3, 4, 5 }; // 2) Initializer list
    std::cout << "Initializer list: ";
    printArray(varArr2);
    
    /*
     * Assignment 
     *  - it is possible to assign values to array using initializer list
     *    (which is not the case in fixed-width array!)
     *  - after empty declaration array contains garbage
     */
    std::array<int, 5> varArr3;
    std::cout << "Array after empty declaration: ";
    printArray(varArr3);

    varArr3 = {1, 2, 3, 4, 5 };
    std::cout << "Assignment after declaration: ";
    printArray(varArr3);
    std::cout << "------------------------------\n";
}

void fill()
{
    std::array<int, 5> varArr { 1, 2, 3, 4, 5 };
    std::cout << "Initial array: ";
    printArray(varArr);

    /*
     * fill(const T& value) -> void
     *  - fill whole array with given value
     */
    varArr.fill(5);
    std::cout << "Fill already filled array: ";
    printArray(varArr);

    std::array<int, 5> varArr2;
    varArr2.fill(3);
    std::cout << "Fill empty array(): ";
    printArray(varArr2);

    std::cout << "------------------------------\n";
}

void at_and_operator()
{
    std::array<int, 5> varArr { 1, 2, 3, 4, 5 };
    std::cout << "Initial array: ";
    printArray(varArr);

    /*
     * We can fetch element in 2 ways:
     *  1) [index]
     *  2) .at(index)
     */
    std::cout << "Fetching element using []: " << varArr[1] << " and .at(): " << varArr.at(3) << '\n';

    /*
     * at(size_type pos) -> reference
     * - returns a reference to the element at specified location pos, with bounds checking
     * - if pos is not within the range of the container, an exception of type std::out_of_range is thrown
     */
    try
    {
        varArr.at(8) = 10;
    }
    catch(const std::out_of_range& e)
    {
        std::cout << "Exception \"out_of_range\" is thrown!: ";
        std::cerr << e.what() << '\n';
    }

    std::cout << "------------------------------\n";
}

void front_and_back()
{
    std::array<int, 5> varArr { 1, 2, 3, 4, 5 };
    std::cout << "Initial array: ";
    printArray(varArr);

    /*
     * front() -> reference
     * - access the first element
     */
    std::cout << "First element of the array using front = " << varArr.front() << '\n';


    /*
     * back() -> reference
     * - access the last element
     */
    std::cout << "Last element of the array using back = " << varArr.back() << '\n';

    std::cout << "------------------------------\n";
}