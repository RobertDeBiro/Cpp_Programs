#include <iostream>

int main()
{
    std::cout << "Enter a single character: ";
    char c;
    std::cin >> c;

    // char can be converted to int in several ways
    std::cout << "1.Option - You entered '" << c << "' which has ASCII code " << static_cast<int>(c) << "\n";
    
    int ascii{ c };
    std::cout << "2.Option - You entered '" << c << "' which has ASCII code " << ascii << "\n";

    std::cout << "3.Option - You entered '" << c << "' which has ASCII code " << (int)c << "\n";
    
    return 0;
}
