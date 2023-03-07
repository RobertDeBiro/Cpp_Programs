/*
 * C++ Primer
 * Exercises section 2.5.2
 *  - Exercise 2.35
 */

#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    const int i = 42;
    
    auto j = i;                     // j is an "int"
    const auto &k = i;              // k is an "const int&" (first const is redundant)
    auto *p = &i;                   // p is an "const int*"
    const auto j2 = i, &k2 = i;     // j2 is an "const int", k2 is an "const int&"

    std::cout << "j = " << j << '\n';
    j = 43;
    std::cout << "j (after update) = " << j << '\n';

    std::cout << "k = " << k << '\n';
    //k = 43;                      // ERROR: const int& cannot be changed

    std::cout << "*p = " << *p << '\n';
    //*p = 43;                     // ERROR: const int* cannot be changed

    std::cout << "j2 = " << j2 << '\n';
    //j2 = 43;                     // ERROR: const int cannot be changed

    std::cout << "k2 = " << k2 << '\n';
    //k2 = 43;                     // ERROR: const int& cannot be changed

    std::cout << "*****************************************************\n";
    return 0;
}