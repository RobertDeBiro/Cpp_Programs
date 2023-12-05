/*
 * 1) insert( const value_type& value ) -> std::pair<iterator, bool>
 *
 * 2) insert( iterator pos, const value_type& value ) -> iterator
 *
 * References:
 *  - https://en.cppreference.com/w/cpp/container/set/insert
 */

#include <iostream>
#include <set>

template <typename T>
void printSet(T varSet)
{
    for(auto elem : varSet)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::set<int> varSet{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "Initial set container: \n";
    printSet(varSet);

    // 1) Insert element into container
    //      - element will be automatically sorted
    varSet.insert(3);
    std::cout << "Container after inserting a value: \n";
    printSet(varSet);

    // We can try to insert a duplicated value, but nothing will happen
    varSet.insert(1);
    std::cout << "Container after inserting duplicated value: \n";
    printSet(varSet);

    std::cout << "-------------------------\n";

    // 2) Insert element in the position as close as possible, just prior to wanted iterator
    //      - elements will be sorted, no matter which iterator we chose
    //      - I am not sure what is the benefit of this syntax, but I think in this way sorting is quicker
    varSet.insert(std::next(varSet.begin(), 3), 7);
    std::cout << "Container after inserting a value near wanted iterator: \n";
    printSet(varSet);

    // ERROR: std::set iterator cannot traverse by using '+' operator!
    //          - I think that is because std::set is a tree
    // varSet.insert((varSet.begin() + 3), 7);

    std::cout << "*****************************************************\n";
    return 0;
}
