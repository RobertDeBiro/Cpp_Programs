#include <iostream>

enum States
{
    CROATIA,
    BIH
};

enum Cities : int
{
    ZAGREB,
    MOSTAR
};

int main()
{
    std::cout << "*****************************************************\n";

    /*
     * Initialize unscoped enums
     */
    States st1{ CROATIA };
    // ERROR: We can't initialize unscoped enum with integer!
    //  - compiler will not implicitly convert an integer to an unscoped enumerator
    // States st2a{ 0 };

    // As a workaround for previous problem, we can cast integer to enum
    States st2b{ static_cast<States>(1) };

    // As of C++17, if we specify the base for enumeration, the compiler will allow
    // us to INITIALIZE an unscoped enumeration using an integral
    Cities ct1{ 0 };
    
    // - however, compiler won't let us to ASSING integral to unscoped enum
    // ct1 = 5;

    /*
     * Initialize integers with unscoped enums
     * - we can initialize integers with enumerations (enums) and enumerators
     * - compiler will implicitly convert an unscoped enum to an integer
     */
    int var1{ st1 };
    int var2{ MOSTAR };
    std::cout << "var1 = " << var1 << "; var2 = " << var2 << '\n';

    /*
     * Printing enums using std::cout
     *  - std::cout will not print enumeration value but rather integer
     *  - workaround is to use switch statement and write enumerations by ourselves as strings
     */
    std::cout << "1. State = " << st1 << '\n';
    std::cout << "2. State = " << st2b << '\n';
    std::cout << "1. City = " << ct1 << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}