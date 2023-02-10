#include <iostream>
#include <vector>

void printVector(const std::vector<int>& varVect)
{
    for(int elem : varVect)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

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
     * std::vector<int> vect(size_type count, const T& value)
     *  - we can fill specified amount of vector elements with the same value
     *  - value_of_elements can be omitted, and then the value is 0
     *  - equivalent to this syntax is std::array<T,N>::fill
     *  - this is the same syntax as "std::string var(n, 'c')"
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

    std::cout << "Update of only one element: ";
    varVect5[0] = 2;
    printVector(varVect5);

    // We can assign vector elements just like we would do with arrays also
    //  - but only existing elements
    //  - if we want to dynamically increase vector we would need to use push-back()
    for(int i = 0; i < static_cast<int>(varVect4.size()); i++)
        varVect4[i] = i;
    std::cout << "Vector assigned as array: ";
    printVector(varVect4);

    std::cout << "*****************************************************\n";
    return 0;
}
