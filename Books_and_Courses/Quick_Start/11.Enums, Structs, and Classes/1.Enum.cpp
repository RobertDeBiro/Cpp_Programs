//* Enumeration (enumerated type, enum)
/**
 *  - compound data type where every possible value is defined as a symbolic constant (enumerator)
 *  - C++ supports two kinds of enumerations:
 *      1) Unscoped enumerations
 *      2) Scoped enumerations
 **/

//* Unscoped enumerations
/**
 *  - syntax:
 *?     enum Enum_Name
 *?     {
 *?         enumerator1,
 *?         enumerator2,
 *?         ...
 *?         enumeratorN
 *?     };
 *  - each enumerator is seperated by a comma
 *  - defintion must end with a semicolon
 *  - enumeration - common to set name starting with a capital letter
 *  - called "unscoped" because they put their enumerator names into the same scope
 *    as the enumeration definition itself
 *  - each enumerator is automatically assigned an integer value based on its position in the enumerator list
 *      - by default, the first enumerator is assigned the integral value 0, and each subsequent enumerator
 *        has a value one greater than the previous enumerator
 **/

#include <iostream>
#include <string>

namespace State
{
// Defining an enumeration (or any user-defined data type) does not allocate any memory –
// memory is allocated when a variable of the enumerated type is defined
enum State
{
    USA,        // assigned 0
    Germany,    // assigned 1
    India,       // assigned 2
    Monaco
};
}

enum City : int
{
    City_New_York,   // assigned 0
    City_Miami,      // assigned 1
    City_Berlin,     // assigned 2
    City_Frankfurt,  // assigned 3
    City_Mumbai,     // assigned 4
    City_Delhi,       // assigned 5
    City_Monaco
};

std::string getState(State::State st)
{
    switch (st)
    {
        case State::USA:        return "USA";
        case State::Germany:    return "Germany";
        case State::India:      return "India";
        default:         return "???";
    }
}

int main()
{
    //* Initialize unscoped enums
    State::State st1{ State::USA }; // memory allocated

    City ct1{ City_New_York };
    
    //* Printing enums using std::cout
    //  - std::cout will not print enumeration value but rather integer
    std::cout << "State = " << st1 << '\n';
    std::cout << "City = " << ct1 << '\n';

    //  - workaround is to use switch statement and write enumerations by ourselves as strings
    std::cout << "State = " << getState(st1) << '\n';
    std::cout << "State = " << getState(State::India) << '\n';

    //! ERROR: We cannot initialize unscoped enum with integer!
    //  - compiler will not implicitly convert an integer to an unscoped enumerator
    // State st2{ 2 };

    // As a workaround for previous problem, we can cast integer to enum
    State::State st2{ static_cast<State::State>(2) };

    // As of C++17, if we specify the base for enumeration, the compiler will allow
    // us to INITIALIZE an unscoped enumeration using an integral
    City ct2{ 0 };
    
    // However, compiler won't let us to ASSING integral to unscoped enum
    // ct2 = 5;

    //* Initialize integers with unscoped enums
    //  - we can initialize integers with enumerations (enums) and enumerators
    //  - compiler will implicitly convert an unscoped enum to an integer
    int var1{ st1 };
    int var2{ City_Mumbai };
    std::cout << "var1 = " << var1 << "; var2 = " << var2 << '\n';

    std::cout << "---------------------------------------------------------\n";

    if(ct1 == City_New_York)
    {
        std::cout << "ct1 is New York!\n";
    }

    return 0;
}