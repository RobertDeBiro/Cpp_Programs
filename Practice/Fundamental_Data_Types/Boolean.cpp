#include <iostream>

void initialization_and_assignment();
void boolalpha();

int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();
    boolalpha();

    std::cout << "*****************************************************\n";
    return 0;
}

void initialization_and_assignment()
{
    // We can initialize boolean to integer value using:

    // 1) copy initialization -> implicit conversion
    bool b1 = 5;
    std::cout << "b1 = " << b1 << "\n";

    // 2) direct initialization -> implicit conversion
    bool b2( 0 );
    std::cout << "b2 = " << b2 << "\n";

    // uniform initialization -> implicit conversion
    //  - from C++17 onwards this is also narrowing conversion,
    //    so we cannot initialize boolean in this way
    //bool b3{ 5 };
    //std::cout << "b3 = " << b3 << "\n";

    std::cout << "------------------------------\n";
}

void boolalpha()
{
    bool b1 = 5;
    bool b2 = 0;
    std::cout << "b1 = " << b1 << "\n";
    std::cout << std::boolalpha; // with std::boolalpha we can print true/false rather then 1/0
    std::cout << "b1 = " << b1 << "\n";
    std::cout << "b2 = " << b2 << "\n";
    std::cout << std::noboolalpha;
    std::cout << "b2 = " << b2 << "\n";

    std::cout << "------------------------------\n";
}