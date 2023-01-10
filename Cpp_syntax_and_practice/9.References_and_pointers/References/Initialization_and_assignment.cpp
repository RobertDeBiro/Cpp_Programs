#include <iostream>

int main()
{
    int i = 0, &r1 = i;
    double j = 5.5, &r2 = j;

    std::cout << "i = " << i << "; r1 = " << r1 << std::endl;
    std::cout << "j = " << j << "; r2 = " << r2 << std::endl;

    // This triggers error: we cannot bind "int" references to "double" object
    int &r3 = j;
    std::cout << "j = " << j << "; r3 = " << r3 << std::endl;

    return 0;
}