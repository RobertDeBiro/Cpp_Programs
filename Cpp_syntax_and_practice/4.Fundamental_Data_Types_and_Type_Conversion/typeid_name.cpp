#include <iostream>
#include <typeinfo> // typeid

int main()
{
    std::cout << "*****************************************************\n";

    /*
     * Check base fundamental types
     */
    std::cout << "Char = " << typeid(char).name() << '\n'; // c
    std::cout << "Short = " << typeid(short).name() << '\n'; // s
    std::cout << "Integer = " << typeid(int).name() << '\n'; // i
    std::cout << "Long = " << typeid(long).name() << '\n'; // l
    std::cout << "Long Long = " << typeid(long).name() << '\n'; // l
    std::cout << "Float = " << typeid(float).name() << '\n'; // f
    std::cout << "Double = " << typeid(double).name() << '\n'; // d
    std::cout << "Pointer to int = " << typeid(int*).name() << '\n'; // Pi

    std::cout << "----------------------------------------\n";

    /*
     * Check modified fundamental types
     */
    int i{ 1 };
    int* pi{ &i };
    int& ri{ i };

    std::cout << "int* = " << typeid(pi).name() << '\n'; // Pi
    std::cout << "int& = " << typeid(ri).name() << '\n'; // i

    const int ci{ 3 };
    const int* cpi{ &ci };
    const int *const ccpi{ &ci };
    const int& cri{ ci };

    std::cout << "const int = " << typeid(ci).name() << '\n'; // i
    std::cout << "const int* = " << typeid(cpi).name() << '\n'; // PKi
    std::cout << "const int *const = " << typeid(ccpi).name() << '\n'; // PKi
    std::cout << "const int& = " << typeid(cri).name() << '\n'; // i

    std::cout << "----------------------------------------\n";

    /*
     * Check type when dealing with conversion
     */
    int a{ 1 };
    double b{ 2.5 };
    std::cout << "integer + double = " << typeid(a + b).name() << "\n"; // d   

    std::cout << "*****************************************************\n";
    return 0;
}
