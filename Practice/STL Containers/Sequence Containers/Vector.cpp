/*
 * std::vector
 *  - SYNTAX:
 *      template<
 *          class T,
 *          class Allocator = std::allocator<T>
 *      > class vector;
 * 
 *  - std::vector is a sequence container, also known as Dynamic Array or Array List
 *     - std::vector is actually a mix of Array and List
 *       - it can access element just like normal array, with complexity O(1)
 *       - it can dynamically increase and decrease, just like list
 * 
 *  - time complexity:
 *     - Random access - constant O(1)
 *     - Insertion or removal of elements at the end - amortized constant O(1)
 *     - Insertion or removal of elements - linear in the distance to the end of the vector O(n)
 * 
 *  Other           Element access          Capacity            Modifiers
 *  + assign        + at                    - empty             - clear
 *                  + operator[]            + size              + insert
 *                  - front                 - max_size          - emplace
 *                  - back                  + reserve           + erase
 *                  - data                  + capacity          + push_back
 *                                                              - emplace_back
 *                                                              + pop_back
 *                                                              + resize
 *                                                              - swap
 * 
 * - more info:
 *    - https://en.cppreference.com/w/cpp/container/vector
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
    std::cout << "Size: " << varVect.size() << "   Capacity: " << varVect.capacity() << '\n';
}

// std::vector functions
void initialization_and_assignment();
// Other
void assign();
// Element_access
void at_and_operator();
// Capacity
void size_capacity();
void reserve();
// Modifiers
void push_pop_back();
void insert();
void erase();
void resize();

int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();
    
    // Other
    assign();

    // Element access
    at_and_operator();

    // Capacity
    size_capacity();
    reserve();

    // Modifiers
    push_pop_back();
    insert();
    erase();
    resize();

    std::cout << "*****************************************************\n";
    return 0;
}

void initialization_and_assignment()
{
    /*
     * Initializations
     */
    std::vector<int> varVect1 { 1, 2, 3, 4, 5 }; // 1) Uniform initialization
    std::cout << "Uniform initialization: ";
    printVector(varVect1);

    std::vector<int> varVect2 = { 1, 2, 3, 4, 5 }; // 2) Initializer list
    std::cout << "Initializer list: ";
    printVector(varVect2);

    /*
     * 3) std::vector<int> vect(size_type count, const T& value)
     *     - we can fill specified amount of vector elements with the same value
     *     - value_of_elements can be omitted, and then the value is 0
     *     - equivalent to this syntax is std::array<T,N>::fill
     */
    std::vector<int> varVect3(5, 1);
    std::cout << "Count values initialization 1: ";
    printVector(varVect3);
    
    std::vector<int> varVect4(5);
    std::cout << "Count values initialization 2: ";
    printVector(varVect4);

    /*
     * Assignment 
     *  - it is possible to declare vector without initialization and afterwards
     *    assign values to vector using initializer list
     */
    std::vector<int> varVect5;
    varVect5 = {1, 2, 3, 4, 5 };
    std::cout << "Assignment after declaration: ";
    printVector(varVect5);
    
    std::cout << "------------------------------\n";
}

void assign()
{
    std::vector<int> varVect { 1, 2, 3, 4, 5 };
    std::cout << "Initial vector: ";
    printVector(varVect);

    /*
     * assign(size_type count, const T& value) -> void
     * - if vector is already initialized and we want to change some of its values
     *   to one specific value, we can use assign() function
     * - it is very similar to syntax "std::vector<int> varVect3(5, 1)"
     *   except this is used when vector is already initialized
     */
    varVect.assign(5, 2);
    std::cout << "Assignment using assign: \n";
    printVector(varVect);

    std::cout << "------------------------------\n";
}

void push_pop_back()
{
    std::vector<int> varVect { 1, 2, 3, 4, 5 };
    std::cout << "Initial vector: ";
    printVector(varVect);

    /*
     * Add and remove values from vector
     */
    std::cout << "Push back: \n";
    varVect.push_back(6);
    printVector(varVect);
    //vect[3] = 6; -> we cannot add a new value in this way!

    std::cout << "Pop back: \n";
    varVect.pop_back();
    printVector(varVect);

    std::cout << "------------------------------\n";
}

void at_and_operator()
{
    std::vector<int> varVect { 1, 2, 3, 4, 5 };
    std::cout << "Initial vector: ";
    printVector(varVect);

    /*
     * We can fetch element in 2 ways:
     *  1) [index]
     *  2) .at(index)
     */
    std::cout << "Fetching element using []: " << varVect[1] << " and .at(): " << varVect.at(3) << '\n';

    /*
     * at(size_type pos) -> reference
     * - returns a reference to the element at specified location pos, with bounds checking
     * - if pos is not within the range of the container, an exception of type std::out_of_range is thrown
     */
    try
    {
        varVect.at(8) = 10;
    }
    catch(const std::out_of_range& e)
    {
        std::cout << "Exception \"out_of_range\" is thrown!: ";
        std::cerr << e.what() << '\n';
    }

    std::cout << "------------------------------\n";
}

void insert()
{
    std::vector<int> varVect { 1, 2, 3, 4, 5 };
    std::cout << "Initial vector: ";
    printVector(varVect);

    /*
     * insert(iterator pos, const T& value) -> iterator
     *  - insert value before pos
     *  - return value is iterator pointing to the new element
     *  - example:
     *     - insert 200 at the beginning of the vector
     *     - after inserting element, first element becomes second
     *       and new element is inserted in front of him
     */
    auto it = varVect.insert(varVect.begin(), 200);
    std::cout << "Insert 200 at the beginning: ";
    printVector(varVect);
 
    /*
     * insert(iterator pos, size_type count, const T& value) -> void
     *  - insert count copies of the value before pos
     *  - return value is iterator pointing to first new element
     *  - example:
     *     - insert 300, 2 times, in first 2 positions of the vector
     */
    varVect.insert(it, 2, 300); 
    std::cout << "Insert 300, 2 times, in first 2 positions of the vector: ";
    printVector(varVect);

    /*
     * insert(iterator pos, InputIt first, InputIt last) -> void
     *  - inserts elements from range [first, last) before pos
     *  - examples:
     *     - insert everything contained inside vect2 to vect1, starting from index 2
     *     - insert array at the beginning of the vector
     *     - insert array at the end of the vector
     */
    std::vector<int> vect2(2, 400);
    varVect.insert(std::next(varVect.begin(), 2), vect2.begin(), vect2.end());
    std::cout << "Insert everything contained inside additional vector, starting from index 2: ";
    printVector(varVect);
 
    int arr[] = { 501,502,503 };
    varVect.insert(varVect.begin(), arr, arr + std::size(arr));
    std::cout << "Insert array at the beginning of the vector: ";
    printVector(varVect);
 
    varVect.insert(varVect.end(), { 601,602,603 } );
    std::cout << "Insert array at the end of the vector: ";
    printVector(varVect);

    std::cout << "------------------------------\n";
}

void erase()
{
    std::vector<int> varVect { 1, 2, 3, 4, 5 };
    std::cout << "Initial vector: ";
    printVector(varVect);

    /*
     * erase(iterator pos) -> iterator
     *  - erase the element from the container, specified by the pos
     */
    varVect.erase(varVect.begin());
    std::cout << "Vector after erasing one element: ";
    printVector(varVect);
 
    /*
     * erase(iterator first, iterator last) -> iterator
     *  - erase the elements from the container, specified by the [first, last)
     */
    varVect.erase(varVect.begin()+2, varVect.begin()+4);
    std::cout << "Vector after erasing scope of elements: ";
    printVector(varVect);

    // Erase element with value 7
    //  - solution that don't work in VS, but here works
    for (auto it = begin(varVect); it != end(varVect); it++)
    {
        if (*it == 2)
        {
            std::cout << "Iterator value before erase = " << *it << '\n';
            varVect.erase(it);
            std::cout << "Iterator value after erase = " << *it << '\n';
        }
    }
    std::cout << "Vector after every erase: ";
    printVector(varVect);

    std::cout << "------------------------------\n";
}

void size_capacity()
{
    std::vector<int> varVect { 1, 2, 3, 4, 5 };
    std::cout << "Initial vector: ";
    printVector(varVect);
    std::cout << "Initial vector size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // Reducing length to 3, whereas capacity remains the same
    //  - once set, capacity can't be shrinked!
    varVect = {1, 2, 3};
    std::cout << "1.Updated vector: ";
    printVector(varVect);
    std::cout << "1.Updated vector size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // Increase both length and capacity to amount of 7
    // - when increasing vector by using assignment, capacity
    //   is increased to the size of the vector
    varVect = {1, 2, 3, 4, 5, 6, 7};
    std::cout << "2.Updated vector: ";
    printVector(varVect);
    std::cout << "2.Updated vector size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // With push_back we are adding one element and increasing vector size
    // - when increasing a vector by using push_back() capacity doubles its
    //   value in order to avoid a lot of coppies
    varVect.push_back(8);
    std::cout << "3.Updated vector: ";
    printVector(varVect);
    std::cout << "3.Updated vector size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    // With pop_back we are removing one element and decreasing vector size
    varVect.pop_back();
    std::cout << "4.Updated vector: ";
    printVector(varVect);
    std::cout << "4.Updated vector size and capacity: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------\n";
}

void reserve()
{
    // Compiler reserves more place then needed, i.e. capacity is most of the time
    // bigger then actual vector size
    //  - compiler does that because resizing is expensive, so to decrease the number
    //    of resize operations

    // If we know our vector will grow to some point, in order to optimize usage of vector
    // we can use reserve() function
    std::vector<int> varVect;
    varVect.reserve(32);
    for(int i = 0; i<32; ++i)
    {
        varVect.push_back(i);
        printVectorSizeAndCapacity(varVect);
    }

    // The moment size becomes bigger than capacity, capacity doubles
    varVect.push_back(33);
    printVectorSizeAndCapacity(varVect);

    // If we reserve smaller value of our capacity and size, nothing will be changed
    varVect.reserve(5);
    std::cout << "Reserve smaller scope then currently having in a vector: ";
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------\n";
}

void resize()
{
    std::vector<int> varVect { 1, 2, 3, 4, 5 };
    std::cout << "Initial vector: ";
    printVector(varVect);

    // By resizing vector only existing elements within new size are left, other are trimmed
    varVect.resize(2);
    std::cout << "Vector resized to a smaller value: ";
    printVector(varVect);
    printVectorSizeAndCapacity(varVect);

    std::cout << "------------------------------\n";
}