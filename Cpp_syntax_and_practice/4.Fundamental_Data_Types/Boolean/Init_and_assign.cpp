#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    //********** Boolean initialization with integer values **********
    // 1) Copy initialization
    //      - implicit conversion
    bool b1 = 5;
    std::cout << "b1 = " << b1 << "\n";

    // 2) Direct initialization
    //      - implicit conversion
    bool b2( 0 );
    std::cout << "b2 = " << b2 << "\n";

    // 3) Uniform initialization
    //      - implicit conversion
    //      - from C++17 onwards this is also narrowing conversion,
    //        so we cannot initialize boolean in this way!
    //!bool b3{ 5 };
    //!std::cout << "b3 = " << b3 << "\n";

    std::cout << "*****************************************************\n";
    return 0;
}
