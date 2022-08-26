#include <iostream>
#include <typeinfo>

int main()
{
    std::cout << "Char = " << typeid(char).name() << '\n'; // c
    std::cout << "Short = " << typeid(short).name() << '\n'; // s
    std::cout << "Integer = " << typeid(int).name() << '\n'; // i
    std::cout << "Long = " << typeid(long).name() << '\n'; // l
    std::cout << "Long Long = " << typeid(long).name() << '\n'; // l
    std::cout << "Float = " << typeid(float).name() << '\n'; // f
    std::cout << "Double = " << typeid(double).name() << '\n'; // d

    int i{ 5 };
    double d{ 2.5 };
    std::cout << "\nCheck the type: integer + double = " << typeid(i + d).name() << "\n"; // d

    return 0;
}
