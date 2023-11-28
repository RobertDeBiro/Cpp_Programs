#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    int i = 0;
    int &r1 = i;
    // When reference is created it must be initialized!
    //! int &r2;

    // We can initialize variable and reference to that variable, in the same statement
    double j = 5.5, &r3 = j;

    std::cout << "i = " << i << "; r1 = " << r1 << std::endl;
    std::cout << "j = " << j << "; r3 = " << r3 << std::endl;

    // We cannot bind "int" references to "double" object
    //! int &r4 = j;

    std::cout << "*****************************************************\n";
    return 0;
}