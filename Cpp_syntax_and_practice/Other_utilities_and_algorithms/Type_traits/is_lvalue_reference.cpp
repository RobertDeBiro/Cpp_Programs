/*
 * References:
 *  - https://en.cppreference.com/w/cpp/types/is_lvalue_reference
 */

#include <iostream>
#include <typeinfo>
#include <type_traits>

class A
{
    int m_x{ 10 };

public:
    int get_x()
    {
        return m_x;
    }
};

template<typename T>
void f(T& param)
{
    std::cout << "T type = " << typeid(T).name() << '\n';
    std::cout << "T reference = " << std::is_lvalue_reference<T>::value << '\n';
    std::cout << "------------------------------\n";
}

int main()
{
    std::cout << "*****************************************************\n";
    std::cout << std::boolalpha;
    
    int x = 27;
    int& rx = x;
    A a;

    // We cannot check the reference of an object, we can check only reference of a type
    //! std::cout << "x reference = " << std::is_lvalue_reference<x>::value << '\n';
    //! std::cout << "rx reference = " << std::is_lvalue_reference<rx>::value << '\n';
    //! std::cout << "a reference = " << std::is_lvalue_reference<a>::value << '\n';

    std::cout << "A reference = " << std::is_lvalue_reference<A>::value << '\n';
    
    std::cout << "f(x): \n";
    f(x);

    std::cout << "f(rx): \n";
    f(rx);

    std::cout << "f(a): \n";
    f(a);

    std::cout << std::noboolalpha;
    std::cout << "*****************************************************\n";
    return 0;
}