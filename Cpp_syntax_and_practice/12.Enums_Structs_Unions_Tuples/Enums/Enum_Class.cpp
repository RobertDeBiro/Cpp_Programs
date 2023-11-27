#include <iostream>

//* Scoped enumeration
enum class States
{
    CROATIA,
    BIH
};

//* Scoped enumeration with specified base
enum class Cities : int
{
    ZAGREB,
    MOSTAR
};

int main()
{
    std::cout << "*****************************************************\n";

    //********** Initialize scoped enums **********
    States st1{ States::BIH };

    // As of C++17, the compiler will allow us to INITIALIZE an unscoped enumeration using an integral
    States st2{ 0 };

    // However, compiler won't let us to ASSING integral to scoped enum
    //! st2 = 5;

    //********** Initialize integers with scoped enums **********
    // We cannot initialize integers with scoped enums and enumerators
    // because compiler won't implicitly convert scoped enum into integer
    //! int var1{ st1 };
    //! int var2{ Cities::ZAGREB };

    // - for the same reason we are not able to print scoped enum
    // std::cout << "State = " << st1 << '\n';

    // As a workaround for previous problem, we can cast scoped enums to integrals (integers or chars)
    std::uint_least8_t j = static_cast<std::uint_least8_t>(st1);
    std::cout << "j = " << j << '\n'; // no value is printed since ASCII of 1 is not printable
    std::cout << "j = " << static_cast<int>(j) << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}