#include <iostream>

enum class States
{
    CROATIA,
    BIH
};

enum class Cities : int
{
    ZAGREB,
    MOSTAR
};

int main()
{
    std::cout << "*****************************************************\n";

    /*
     * Initialize scoped enums
     */
    States st1{ States::BIH };
    // As of C++17, the compiler will allow us to INITIALIZE an unscoped enumeration using an integral
    States st2{ 0 };

    // However, compiler won't let us to ASSING integral to scoped enum
    // st2 = 5;

    /*
     * Initialize integers with scoped enums
     * - we cannot initialize integers with scoped enumerations (enums) and enumerators
     *   because compile won'r implicitly convert scoped enum into integer
     */
    // int var1{ st1 };
    // int var2{ Cities::ZAGREB };

    // - for the same reason we are not able to print scoped enum
    // std::cout << "State = " << st1 << '\n';

    // As a workaround for previous problem, we can cast scoped enums to integrals (integers or chars)
    std::uint_least8_t j = static_cast<std::uint_least8_t>(st1);
    std::cout << "j = " << j << '\n'; // here nothing will be printes sicne ASCII of 1 is not printable
    std::cout << "j = " << static_cast<int>(j) << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}