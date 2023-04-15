#include <iostream>
#include <iomanip>

int main()
{
    //* Floating point variables
    /**
     *  - variables that can hold a real number (a number with a decimal place)
     *  - when using always include at least one decimal place
     *  - floating point literals are by default typed as double
     *      - float literal - add suffix f
     *      - long double literal - add suffix l
     *  - may be printed with scientific notation
     **/
    double d1 = 100.0;
    float f1 = 3.14f; // adding "f" suffix
    long double ld1 = 1564.22l; // adding "l" suffix
    
    std::cout << "Double d1 = " << d1 << '\n';
    std::cout << "Float f1 = " << f1 << '\n';
    std::cout << "Long double ld1 = " << ld1 << '\n';

    std::cout << "----------------------------------------------------\n";

    ld1 = 1'564'012'321.0l;

    // Printed with:
    //  - scientific notation
    //  - precision of 6 significant digits
    // => we have rounding error
    std::cout << "Long double ld1 = " << ld1 << '\n';

    std::cout << std::setprecision(10);
    std::cout << "Long double ld1 = " << ld1 << '\n'; // printed with precision of 10 significant digits

    d1 = 5.0123456789;
    std::cout << "Double d1 = " << d1 << '\n';

    std::cout << std::setprecision(5);
    std::cout << "Double d1 = " << d1 << '\n';

    std::cout << "---------------------------------------\n";

    ////////////////////////////////////////////////////////////////////////////////////////////////

    //* Inf and Nan
    /**
     *  - there are two special categories of floating point numbers:
     *      1. Inf - infinity
     *      2. NaN - Not a Number
     **/
    double zero{ 0.0 };
    
    double posinf{ 5.0 / zero };
    std::cout << "positive infinity = " << posinf << '\n';

    double neginf{ -5.0 / zero };
    std::cout << "negative infinity = " << neginf << '\n';

    double nan { zero / zero }; // not a number (mathematically invalid)
    std::cout << "not a number = " << nan << '\n';

    return 0;
}