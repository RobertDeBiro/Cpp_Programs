#include <iostream>
#include <typeinfo> // typeid

int main()
{
    std::cout << "Char = " << typeid(char).name() << '\n'; // c
    std::cout << "Short = " << typeid(short).name() << '\n'; // s
    std::cout << "Integer = " << typeid(int).name() << '\n'; // i
    std::cout << "Long = " << typeid(long).name() << '\n'; // l
    std::cout << "Long Long = " << typeid(long).name() << '\n'; // l
    std::cout << "Float = " << typeid(float).name() << '\n'; // f
    std::cout << "Double = " << typeid(double).name() << '\n'; // d
    std::cout << "Pointer to int = " << typeid(int*).name() << '\n'; // Pi

    int i{ 5 };
    double d{ 2.5 };
    std::cout << "\nCheck the type: integer + double = " << typeid(i + d).name() << "\n"; // d

    int* j{ &i };
    std::cout << "j = " << typeid(j).name() << '\n'; // Pi

    return 0;
}
