/*
 * References:
 *  - https://en.cppreference.com/w/cpp/types/is_const
 */

#include <iostream>
#include <typeinfo>
#include <type_traits>

template<typename T>
void f1(T& param)
{
    std::cout << "T type = " << typeid(T).name() << '\n';
    std::cout << "T const = " << std::is_const<T>::value << '\n';
    std::cout << "------------------------------\n";
}

// If we send 'const int' argument to 'T', since we already have 'const' that makes 'param' unchangeable
// only 'int' data type would substitute 'T' and not 'const int', since 'const' would be redundant
template<typename T>
void f2(const T& param)
{
    std::cout << "T type = " << typeid(T).name() << '\n';
    std::cout << "T const = " << std::is_const<T>::value << '\n';
    std::cout << "------------------------------\n";
}

int main()
{
    std::cout << "*****************************************************\n";
    std::cout << std::boolalpha;

    int x = 27;
    const int cx = x;
    const int& rx = x;

    //* Function parameter is reference
    std::cout << "f1(x): \n";
    f1(x);

    std::cout << "f1(cx): \n";
    f1(cx);

    std::cout << "f1(rx): \n";
    f1(rx);

    /////////////////////////////////////////////////////////////////////

    //* Function parameter is reference to const
    std::cout << "f2(x): \n";
    f2(x);

    std::cout << "f2(cx): \n";
    f2(cx);
    
    std::cout << "f2(rx): \n";
    f2(rx);

    std::cout << std::noboolalpha;
    std::cout << "*****************************************************\n";
    return 0;
}