#include <iostream>
#include <list>

void printList(const std::list<int>& varList)
{
    for(int elem : varList)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    //********** Initializations **********
    // Uniform initialization
    std::list<int> varList1 { 1, 2, 3, 4, 5 };
    std::cout << "Uniform initialization: ";
    printList(varList1);

    // Initializer list
    std::list<int> varList2 = { 1, 2, 3, 4, 5 };
    std::cout << "Initializer list: ";
    printList(varList2);

    //* std::list<int> varList(size_type count, const T& value)
    //  - we can fill specified amount of list elements with the same value
    //  - value of elements can be omitted, and then the value is '0'
    //  - equivalent to this syntax is 'std::vector<int> vect(size_type count, const T& value)'
    std::list<int> varList3(5, 1);
    std::cout << "Count values initialization 1: ";
    printList(varList3);
    
    std::list<int> varList4(5);
    std::cout << "Count values initialization 2: ";
    printList(varList4);

    //********** Assignment **********
    //  - it is possible to declare list without initialization and afterwards
    //    assign values to list using initializer list
    std::list<int> varList5;
    varList5 = {1, 2, 3, 4, 5 };
    std::cout << "Assignment after declaration: ";
    printList(varList5);

    // Following is not possible - fast random access with 'operator[]' is not supported 
    //! varList5[0] = 2;

    std::cout << "*****************************************************\n";
    return 0;
}
