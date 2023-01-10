#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter some string to check its length: ";
    std::string str;
    std::getline(std::cin >> std::ws, str);

    std::cout << "String " << str << " has length of " << str.length() << " characters!\n";

    return 0;
}
