/*
 * Lambdas can only access specific kinds of identifiers:
 *  - global identifiers
 *  - entities that are known at compile time (constexpr)
 *  - entities with static storage duration
 */

#include <iostream>

class Storage
{
    int m_c{ 7 };
public:
    // Member variable with automatic storage duration - needs to be captured
    int m_a{ 10 };

    // Member variable with static storage duration - doesn't need to be captured
    static int m_b;

    void someFunct();
};

int Storage::m_b{ 20 };

void Storage::someFunct()
{
    // When lambda is used inside member function, in order to access member variables
    // we need to send object "this"
    //  - object "this" can be sent in two ways:
    //      1)  this - captures the object by reference
    //      2) *this - captures the object by value
    //  - more info:
    //    https://stackoverflow.com/questions/16323032/why-cant-i-capture-this-by-reference-this-in-lambda
    auto lambdaVarInFunc =
        [this]() { std::cout << "Lambda: m_c = " << m_c << '\n'; };
    
    lambdaVarInFunc();
}

// Global variable - doesn't need to be captured
int k{ 2 };

int main()
{
    std::cout << "*****************************************************\n";

    int x{ 3 };
    int y{ 4 }; // local variable - needs to be captured
    constexpr int z{ 5 }; // constexpr variable doesn't need to be captured
    Storage s;

    // Local variables can be used in lambda in two ways:
    //  1) Sent as input parameter - "x"
    //  2) Captured - "y"
    //  - the main difference is that value for "x" needs to be sent to lambdaObject call,
    //    whereas the value for "y" doesn't have to, since "y" is already captured
    auto lambdaObject =
        [y](const int x, Storage s)
        {
            std::cout << "x = " << x << '\n';
            std::cout << "y = " << y << '\n';
            std::cout << "z = " << z << '\n';
            std::cout << "k = " << k << '\n';
            std::cout << "s.m_a = " << s.m_a << '\n';
            std::cout << "S::m_b = " << Storage::m_b << '\n';
        };

    std::cout << "Execute lambda: \n";
    lambdaObject(x, s);

    std::cout << "-----------------------------\n";

    std::cout << "Execute lambda inside member function: \n";
    s.someFunct();

    std::cout << "*****************************************************\n";
    return 0;
}
