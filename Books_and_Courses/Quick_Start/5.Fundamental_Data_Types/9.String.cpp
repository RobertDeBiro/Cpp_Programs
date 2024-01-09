#include <iostream>
#include <string>

int main()
{
    //* String
    /**
     *  - collection of sequential characters
     *  - included as part of string library
     **/
    std::string str1 = "Hello World!";
    std::cout << str1 << std::endl;

    str1 = "Bye bye World!";
    std::cout << str1 << std::endl;

    str1 = "";
    std::cout << str1 << std::endl;

    /////////////////////////////////////////////////////////////////////////

    //* String input
    /**
     *  - for input the best is to use std::getline
     *  - syntax:
     *?      std::getline(std::cin >> std::ws, string_variable)
     **/
    // std::cout << "Enter your first name: ";
    // std::string firstName;
    // std::cin >> firstName;
    // std::cout << "First name: " << firstName << '\n';

    // std::cout << "Enter your full name: ";
    // std::string fullName;
    // std::cin >> fullName;
    // std::cout << "Full name: " << fullName << '\n';

    // std::cin >> fullName;
    // std::cout << "Full name: " << fullName << '\n';

    std::cout << "Insert some character: ";
    char c;
    std::cin >> c;

    std::cout << "Enter your full name: ";
    std::string fullName;
    std::getline(std::cin >> std::ws, fullName);
    std::cout << "Full name: " << fullName << '\n';

    /////////////////////////////////////////////////////////////////////////

    // length() is string class member function
    std::cout << "String " << fullName << " has length of " << fullName.length() << " characters!\n";

    return 0;
}
