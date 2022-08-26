/*
 * std::set
 *  - SYNTAX:
 *      template<
 *          class Key,
 *          class Compare = std::less<Key>,
 *          class Allocator = std::allocator<Key>
 *      > class set;
 * 
 *  - std::set is an associative container that contains a sorted set of unique objects of type Key
 *  - sorting is done using the key comparison function Compare
 *  - search, removal, and insertion operations have logarithmic complexity
 *  - usually implemented as red-black trees
 *
 *  Capacity           Modifiers           Lookup          Observers
 *  - empty            - clear             - count         - key_comp
 *  - size             + insert            + find          - value_comp
 *  - max_size         + emplace           - contains
 *                     - emplace_hint      - equal_range
 *                     + erase             - lower_bound
 *                     - swap              - upper_bound
 *                     - extract
 *                     - merge
 */

#include <iostream>
#include <set>

// User-defined data types
class Person
{
public:
    int age{};
    std::string name{};

    bool operator < (const Person& rhs) const { return age < rhs.age; } // operator for std::less implementation (default one)
    bool operator > (const Person& rhs) const { return age > rhs.age; } // operator for std::greater implementation
};

class A
{
public:
    int m_x;
    A(int x = 0) : m_x{x} { std::cout << "Construct\n"; }
    A(const A& rhs)
    {
        m_x = rhs.m_x;
        std::cout << "Copy\n";
    }

    bool operator < (const A& rhs) const { return m_x < rhs.m_x; }
};

// Function template
template <typename T>
void printSet(T varSet)
{
    for(auto elem : varSet)
        std::cout << elem << ' ';
    std::cout << '\n';
}

// Function template specialization 1
template<>
void printSet(std::set<Person> varSet)
{
    for(auto elem : varSet)
        std::cout << elem.name << ' ' << elem.age << '\n';
}

// Function template specialization 2
template<>
void printSet(std::set<Person, std::greater<>> varSet)
{
    for(auto elem : varSet)
        std::cout << elem.name << ' ' << elem.age << '\n';
}

// std::set functions
void initialization_and_assignment();
// Modifiers
void insert();
void emplace();
void erase();
// Lookup
void find();

int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();
    
    // Modifiers
    insert();
    emplace();
    erase();

    // Lookup
    find();

    std::cout << "*****************************************************\n";
    return 0;
}


void initialization_and_assignment()
{
    /*
     * std::set saves unique elements in sorted order
     *  - by default elements are sorted in ascending order - means that std::less<> is used
     *  - if we want to sort in descending order, we can use std::greater<>
     */
    std::set<int> varSet1{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "Initial set container: \n";
    printSet(varSet1);

    std::set<int, std::less<>> varSet2{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "std::less set container: \n";
    printSet(varSet1);

    std::set<int, std::greater<>> varSet3{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "std::greater set container: \n";
    printSet(varSet3);

    /*
     * User defined data in std::set container:
     *  - in order to declare user-defined std::set container, we need to tell to the
     *    std::set how to compare the elements and sort them
     *  - we do that by using overload operator inside user-defined data type
     */
    std::set<Person> varSet4{ {4, "Luka"}, {29, "Martina"}, {2, "Toma"} };
    std::cout << "user-defined data set container: \n";
    printSet(varSet4);

    std::set<Person, std::greater<>> varSet5{ {4, "Luka"}, {29, "Martina"}, {2, "Toma"} };
    std::cout << "std::greater user-defined data set container with: \n";
    printSet(varSet5);

    std::cout << "------------------------------\n";
}

void insert()
{
    std::set<int> varSet{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "Initial set container: \n";
    printSet(varSet);

    /*
     * insert(const value_type& value) -> iterator
     *  - insert element into container
     *  - element will be automatically sorted
     */
    varSet.insert(3);
    std::cout << "Container after inserting a value: \n";
    printSet(varSet);

    // We can try to insert a duplicated value, but nothing will happen
    varSet.insert(1);
    std::cout << "Container after inserting duplicated value: \n";
    printSet(varSet);

    /*
     * insert(iterator hint, const value_type& value) -> iterator
     *  - insert element in the position as close as possible, just prior to iterator hint 
     *  - elements will be sorted, no matter which iterator we chose
     *  - I am not sure what is the benefit of this syntax, but I think in this way sorting is quicker
     */
    varSet.insert(std::next(varSet.begin(), 3), 7);
    std::cout << "Container after inserting a value: \n";
    printSet(varSet);

    // std::set iterator cannot traverse by using '+' operator!
    //  - I think that is because std::set is a tree
    //varSet.insert(varSwet.begin() + 3), 7);

    std::cout << "------------------------------\n";
}

void emplace()
{
    std::cout << "Using set.insert(): \n";
    std::set<A> setInsert;
    A a(10);
    setInsert.insert(a);
    for (const auto& elem : setInsert)
        std::cout << "setInsert elements: " << elem.m_x << '\n';
    std::cout << '\n';

    /*
     * template< class... Args >
     * emplace(Args&&... args) -> std::pair<iterator, bool>
     *  - emplace doesn't call copy constructor because it doesn't copy element but rather move it
     *  - we are sending the values of the object as parameter in emplace()
     *  - it is not used when working with primitive types because there is no benefits in regards to insert()
     */
    std::cout << "Using set.emplace(): \n";
    std::set<A> setEmplace;
    setEmplace.emplace(10);
    for (const auto& elem : setEmplace)
        std::cout << "setEmplace elements: " << elem.m_x << '\n';
    
    std::cout << "------------------------------\n";
}

void erase()
{
    std::set<int> varSet{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "Initial set container: \n";
    printSet(varSet);

    varSet.erase(std::next(varSet.begin(), 2));
    std::cout << "Container after erasing an element: \n";
    printSet(varSet);

    std::cout << "------------------------------\n";
}

void find()
{
    std::set<int> varSet{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "Initial set container: \n";
    printSet(varSet);

    auto it = varSet.find(8);
    varSet.erase(it);
    std::cout << "Container after erasing found element: \n";
    printSet(varSet);

    std::cout << "------------------------------\n";
}