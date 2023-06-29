#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int a{};
    std::cin >> a;

    if (a > 10)
        std::cout << a << " is greater than 10\n";
    // else
    //     std::cout << a << " is not greater than 10\n";
    //     std::cout << a << " is less or equal to 10\n"; //! not allowed if not using block

    // -> ADDING A BLOCK

    //////////////////////////////////////////////////////////////////////////
/*
    // Even though we may not use blocks, if-else uses them implicitly
    //  - following results with error
    if (true)
        int x{ 5 };
    else
        int x{ 6 };

    std::cout << x << '\n';
*/

    return 0;
}