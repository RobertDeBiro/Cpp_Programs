#include <iostream>

class Storage
{
    // Captured as object this
    int m_c{ 7 };
public:
    // Member variable with automatic storage duration
    //  - when used in lambda needs to be captured or sent as parameter
    int m_a{ 10 };

    // Member variable with static storage duration
    //  - when used in lambda doesn't need to be captured
    static int m_b;

    void someFunct();
};

void Storage::someFunct()
{
    // When lambda is used inside member function, in order to use member variables
    // we need to send object "this"
    // Object "this" can be sent in two ways:
    //  1)  this - captures the object by reference
    //  2) *this - captures the object by value
    // - more info:
    //   https://stackoverflow.com/questions/16323032/why-cant-i-capture-this-by-reference-this-in-lambda
    auto lambdaVarInFunc =
        [this]() { std::cout << "Lambda: m_c = " << this->m_c << '\n'; };
    
    lambdaVarInFunc();
}

// Static member variable needs to be intialized outside of the class definition
int Storage::m_b{ 20 };

// Global variable
//  - when used in lambda doesn't need to be captured
int k{ 2 };

int main()
{
    // Local variables can be used in lambda in two ways:
    int x{ 3 }; // 1) Sent as input parameter
    int y{ 4 }; // 2) Captured

    // constexpr variable
    //  - when used in lambda doesn't need to be captured
    constexpr int z{ 5 };

    // Class object behaves as normal local variable
    Storage s;

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

    lambdaObject(x, s);
    s.someFunct();

    return 0;
}
