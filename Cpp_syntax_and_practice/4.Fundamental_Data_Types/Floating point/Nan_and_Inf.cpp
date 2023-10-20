#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    //********** Division by zero **********
    // positive number / zero = inf
    double zero {0.0};
    double posinf { 5.0 / zero };
    std::cout << "positive infinity = " << posinf << '\n';


    // negative number / zero = -inf
    double neginf { -5.0 / zero };
    std::cout << "negative infinity = " << neginf << '\n';


    // zero / zero = -nan
    double nan { zero / zero }; // not a number (mathematically invalid)
    std::cout << "not a number = " << nan << '\n';


    //********** Save "division by zero" into variable **********
    //  - when division by zero is saved inside int variable we will have arithmetic exception
    //!int x{};
    //!int z{ 12 / x };
	//!std::cout << "12 / " << x << " = " << z << '\n';

    //  - when division by zero is saved inside double variable we will have inf/-inf value saved
    //    (like in first example with posinf variable)
    //  - this will work because "inf" and "-inf" are actually typed with "double"
    std::cout << "inf/-inf type is: " << typeid(posinf).name() << '\n'; // Pi

    std::cout << "*****************************************************\n";
    return 0;
}
