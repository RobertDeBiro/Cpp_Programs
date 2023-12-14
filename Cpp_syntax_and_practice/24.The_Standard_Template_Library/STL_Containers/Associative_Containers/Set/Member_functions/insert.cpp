#include <iostream>
#include <set>

template <typename T>
void printSet(T varSet)
{
    for(const auto& elem : varSet)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::set<int> varSet{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "Initial set container: \n";
    printSet(varSet);

    //* Insert element into container
    //  - element will be automatically sorted
    varSet.insert(3);
    std::cout << "Container after inserting a value: \n";
    printSet(varSet);

    //* Insert already existing value
    //  - we can try to insert a duplicated value, but nothing will happen
    varSet.insert(1);
    std::cout << "Container after inserting duplicated value: \n";
    printSet(varSet);

    std::cout << "------------------------------\n";

    //* Insert element in the position as close as possible, just prior to wanted iterator
    //  - inserting an element '7' prior to index '3'
    //  - if we know for sure that our element should be placed prior to specific index (place in 'set')
    //    we can use this syntax because sorting will be faster
    varSet.insert(std::next(varSet.begin(), 3), 7);
    std::cout << "Container after inserting a value near wanted iterator: \n";
    printSet(varSet);

    // Elements will be sorted, no matter which iterator we choose
    varSet.insert(std::next(varSet.begin(), 1), 6);
    std::cout << "Container after inserting a value near wanted iterator: \n";
    printSet(varSet);

    // 'std::set' iterator cannot traverse by using '+' operator, due to how it is internally implemented
    //! varSet.insert((varSet.begin() + 3), 7);

    std::cout << "*****************************************************\n";
    return 0;
}
