#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    std::cout << "Enter some string to check its length: ";
    std::string str;
    std::getline(std::cin >> std::ws, str);

    std::cout << "String " << str << " has length of " << str.length() << " characters!\n";

    std::cout << "*****************************************************\n";
    return 0;
}
