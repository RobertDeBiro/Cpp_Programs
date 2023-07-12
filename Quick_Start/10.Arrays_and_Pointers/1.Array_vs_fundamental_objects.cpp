//* Arrays
/**
 *  - an aggregate data type that lets us access many variables of the same type through a single identifier
 *  - syntax:
 *?   int array_obj[array_length]
 *      -> "array_length" of variables typed with "int"
 *  - each of the variables in an array is called an element
 *  - [] - subscript operator
 *  - subscript - inside subscript operator
 **/

int getsubscript()
{
    return 1;
}

#include <iostream>

int main()
{
    //* Initialize 5 int variables
    int prime0 = 2;
    int prime1 = 3;
    double spy1 = 10.0;
    int prime2 = 5;
    int prime3 = 7;
    double spy2 = 20.0;
    int prime4 = 11;

    //* Declare array containing 5 int variables (elements)
    int prime[5];
    prime[0] = 2;   // Assign array element 1
    prime[1] = 3;   // Assign array element 2
    prime[2] = 5;   // Assign array element 3
    prime[3] = 7;   // Assign array element 4
    prime[4] = 11;  // Assign array element 5

    //* Print variables addresses
    std::cout << "prime0:\t\t value = " << prime0 << ";\t address = " << &prime0 << '\n';
    std::cout << "prime1:\t\t value = " << prime1 << ";\t address = " << &prime1 << '\n';
    //std::cout << "spy1:\t\t value = " << spy1 << ";\t address = " << &spy1 << '\n';
    std::cout << "prime2:\t\t value = " << prime2 << ";\t address = " << &prime2 << '\n';
    std::cout << "prime3:\t\t value = " << prime3 << ";\t address = " << &prime3 << '\n';
    //std::cout << "spy2:\t\t value = " << spy2 << ";\t address = " << &spy2 << '\n';
    std::cout << "prime4:\t\t value = " << prime4 << ";\t address = " << &prime4 << '\n';

    std::cout << "------------------------------------------------------------\n";

    //* Print array elements addresses
    std::cout << "prime[0]:\t value = " << prime[0] << ";\t address = " << &prime[0] << '\n';
    std::cout << "prime[1]:\t value = " << prime[1] << ";\t address = " << &prime[1] << '\n';
    std::cout << "prime[2]:\t value = " << prime[2] << ";\t address = " << &prime[2] << '\n';
    std::cout << "prime[3]:\t value = " << prime[3] << ";\t address = " << &prime[3] << '\n';
    std::cout << "prime[4]:\t value = " << prime[4] << ";\t address = " << &prime[4] << '\n';

    //* Print overflowed array elements
    // std::cout << "prime[-2]:\t value = " << prime[-2] << ";\t address = " << &prime[-2] << '\n';
    // std::cout << "prime[-1]:\t value = " << prime[-1] << ";\t address = " << &prime[-1] << '\n';
    // std::cout << "prime[5]:\t value = " << prime[5] << ";\t address = " << &prime[5] << '\n';
    // std::cout << "prime[6]:\t value = " << prime[6] << ";\t address = " << &prime[6] << '\n';
    // std::cout << "prime[6]:\t value = " << prime[7] << ";\t address = " << &prime[7] << '\n';

    std::cout << "------------------------------------------------------------\n";

    //* Array subscripts
    //  - must be integral data type (char, short, long, long long, bool, enum)
    //  - can be a:
    //      - literal value
    //      - variable
    //      - expression that evaluates to an integral type
    //  - the length of these kind of arrays must be a compile-time constant hence these arrays are also
    //    called fixed arrays
    //  - this means that for subscript we cannot use value that must be inserted during runtime
    //    (even though some compilers allow that)
    int var_subscript = 1;
    std::cout << "prime[variable]:\t value = " << prime[var_subscript] << '\n';
    std::cout << "prime[expression]:\t value = " << prime[getsubscript()] << '\n';

    return 0;
}