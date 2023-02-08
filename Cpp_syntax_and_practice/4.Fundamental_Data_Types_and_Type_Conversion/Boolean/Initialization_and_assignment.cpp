#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    // We can initialize boolean to integer value using:

    // 1) copy initialization -> implicit conversion
    bool b1 = 5;
    std::cout << "b1 = " << b1 << "\n";

    // 2) direct initialization -> implicit conversion
    bool b2( 0 );
    std::cout << "b2 = " << b2 << "\n";

    // 3) uniform initialization -> implicit conversion
    //      - from C++17 onwards this is also narrowing conversion,
    //        so we cannot initialize boolean in this way
    //bool b3{ 5 };
    //std::cout << "b3 = " << b3 << "\n";

    std::cout << "*****************************************************\n";
    return 0;
}
