#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    std::cout << "Enter a single character: ";
    char c;
    std::cin >> c;

    // Char can be converted to int in several ways
    // 1) Use static_cast
    std::cout << "1.Option - You entered '" << c << "' which has ASCII code "
              << static_cast<int>(c) << "\n";
    
    // 2) Assign char to int
    int ascii{ c };
    std::cout << "2.Option - You entered '" << c << "' which has ASCII code " << ascii << "\n";

    // 3) Use C-style conversion
    std::cout << "3.Option - You entered '" << c << "' which has ASCII code " << (int)c << "\n";

    std::cout << "*****************************************************\n";
    return 0;
}
