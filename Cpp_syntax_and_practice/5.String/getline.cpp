#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your full name: ";
    std::string fullName;
    
    // the std::ws input manipulator tells std::cin to ignore any leading whitespace
    // that may be left from previous std::cin inputs
    std::getline(std::cin >> std::ws, fullName);

    std::cout << "Fullname = " << fullName << '\n';

    return 0;
}