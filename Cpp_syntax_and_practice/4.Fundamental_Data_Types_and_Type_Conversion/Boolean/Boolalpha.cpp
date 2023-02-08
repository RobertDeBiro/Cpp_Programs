/*
 * With std::boolalpha and we can print true/false rather then 1/0
 */

#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    bool b1 = 5;
    bool b2 = 0;

    std::cout << "b1 = " << b1 << "\n";

    std::cout << std::boolalpha;
    std::cout << "b1 = " << b1 << "\n";
    std::cout << "b2 = " << b2 << "\n";
    
    std::cout << std::noboolalpha;
    std::cout << "b2 = " << b2 << "\n";

    std::cout << "*****************************************************\n";
    return 0;
}
