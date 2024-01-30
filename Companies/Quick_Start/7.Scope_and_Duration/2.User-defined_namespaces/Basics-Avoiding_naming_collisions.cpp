//* Namespaces
/**
 *  - used to address naming collision (naming conflict) errors
 *  - typically non-capitalized
 *  - two different approaches:
 *      1. Scope resoultion operator ( :: )
 *          - tells the compiler that the identifier specified by the right-hand operand
 *            should be looked for in the scope of the left-hand operand
 *          - example:
 *?             std::cout
 *          - preferred
 *      2. Using statements
 *          a) Using declaration
 *          b) Using directives
 *          -> explained in seperate lesson
 **/

#include <iostream>

namespace int_div
{
    int divide(int x, int y)
    {
        return x / y;
    }
}

namespace float_div
{
    double divide(int x, int y)
    {
        return static_cast<double>(x) / y;
    }
}

int divide(int x, int y)
{
    return x % y;
}

int x = 4;

int main()
{
    int x = 8;
    int y = 3;
    std::cout << "Int division: " << x << " / " << y << " = " << int_div::divide(x, y) << '\n';
    std::cout << "Float division " << x << " / " << y << " = " << float_div::divide(x, y) << '\n';
    std::cout << "Remainder from int division " << x << " % " << y << " = " << divide(x, y) << '\n';

    // When using the scope resolution operator without any preceding namespace, compiler will look
    // for identifier in the global namespace
    std::cout << "Remainder from int division " << ::x << " % " << y << " = " << divide(::x, y) << '\n';
    std::cout << "Remainder from int division " << x << " % " << y << " = " << ::divide(x, y) << '\n';

    return 0;
}