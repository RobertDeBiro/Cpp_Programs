//* Sizeof operator
/**
 *  - unary operator that takes either a type or a variable, and returns its size in bytes
 *  - syntax:
 *?     sizeof (data type / variable)
 **/

#include <iostream>

int main()
{
    // sizeof(data type)
    std::cout << "bool:\t\t" <<         sizeof(bool)        << " bytes\n";
    std::cout << "char:\t\t" <<         sizeof(char)        << " bytes\n";
    std::cout << "wchar_t:\t" <<        sizeof(wchar_t)     << " bytes\n";
    std::cout << "char16_t:\t" <<       sizeof(char16_t)    << " bytes\n";
    std::cout << "char32_t:\t" <<       sizeof(char32_t)    << " bytes\n";
    std::cout << "short:\t\t" <<        sizeof(short)       << " bytes\n";
    std::cout << "int:\t\t" <<          sizeof(int)         << " bytes\n";
    std::cout << "long:\t\t" <<         sizeof(long)        << " bytes\n";
    std::cout << "long long:\t" <<      sizeof(long long)   << " bytes\n";
    std::cout << "float:\t\t" <<        sizeof(float)       << " bytes\n";
    std::cout << "double:\t\t" <<       sizeof(double)      << " bytes\n";
    std::cout << "long double:\t" <<    sizeof(long double) << " bytes\n";

    // sizeof(variable)
    int x{};
    std::cout << "\nx is " << sizeof(x) << " bytes\n";

    return 0;
}