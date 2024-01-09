#include <iostream>
#include <typeinfo>

int main()
{
    short a = 2;
    std::cout << "a value = " << a << '\n';
    std::cout << "a address = " << &a << '\n';
    std::cout << "a value (after dereferencing address) = " << *&a << '\n';
    std::cout << "a type = " << typeid(a).name() << '\n';
    std::cout << "&a type = " << typeid(&a).name() << '\n';

    std::cout << "-----------------------------------------\n";

    short* p = &a;
    std::cout << "p value = " << p << '\n';                 // address of variable "a"
    std::cout << "p address = " << &p << '\n';
    std::cout << "p type = " << typeid(p).name() << '\n';
    std::cout << "p dereference = " << *p << '\n';          // value of variable "a"
    // p = 0x5ffe8e;    //! We cannot assign address to a pointer variable
    // p = 2;           //! We cannot assign a number to a pointer variable

    std::cout << "-----------------------------------------\n";

    //* size of pointer
    std::cout << "Size of pointer on my PC: " << sizeof(p) << "\n";

    return 0;
}