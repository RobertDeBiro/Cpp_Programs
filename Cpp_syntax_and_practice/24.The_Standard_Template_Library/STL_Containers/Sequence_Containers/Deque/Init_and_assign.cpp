#include <iostream>
#include <deque>

void printDeque(const std::deque<int>& varDeq)
{
    for(int elem : varDeq)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    //* Initializations
    // Uniform initialization
    std::deque<int> varDeq1 { 1, 2, 3, 4, 5 };
    std::cout << "Uniform initialization: ";
    printDeque(varDeq1);

    // Initializer list
    std::deque<int> varDeq2 = { 1, 2, 3, 4, 5 };
    std::cout << "Initializer list: ";
    printDeque(varDeq2);

    /*
     * - we can fill specified amount of deque elements with the same value
     * - value_of_elements can be omitted, and then the value is 0
     */
    //* std::deque<int> vect(size_type count, const T& value)
    //  - we can fill specified amount of deque elements with the same value
    //  - value of elements can be omitted, and then the value is '0'
    //  - equivalent to this syntax is 'std::vector<int> vect(size_type count, const T& value)'
    std::deque<int> varDeq3(5, 1);
    std::cout << "Count values initialization 1: ";
    printDeque(varDeq3);
    
    std::deque<int> varDeq4(5);
    std::cout << "Count values initialization 2: ";
    printDeque(varDeq4);

    //* Assignment 
    //  - it is possible to declare deque without initialization and afterwards
    //    assign values to deque using initializer list
    std::deque<int> varDeq5;
    varDeq5 = {1, 2, 3, 4, 5 };
    std::cout << "Assignment after declaration: ";
    printDeque(varDeq5);

    std::cout << "Update of only one element: ";
    varDeq5[0] = 2;
    printDeque(varDeq5);

    // We can assign deque elements just like we would do with arrays also
    //  - but only existing elements
    //  - if we want to dynamically increase deque we would need to use 'push_back()'
    for(int i = 0; i < static_cast<int>(varDeq4.size()); i++)
        varDeq4[i] = i;
    std::cout << "Vector assigned as array: ";
    printDeque(varDeq4);

    std::cout << "*****************************************************\n";
    return 0;
}
