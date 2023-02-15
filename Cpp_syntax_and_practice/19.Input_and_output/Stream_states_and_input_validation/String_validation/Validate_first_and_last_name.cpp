#include <iostream>
#include <string>
#include <string_view>
#include <algorithm> // std::all_of
#include <cctype> // std::isalpha, std::isspace

bool isValidName(std::string_view name)
{
    return std::all_of(name.begin(), name.end(), [](char ch) {
                       return (std::isalpha(ch) || std::isspace(ch));
            });
}

int main()
{
    std::cout << "*****************************************************\n";

    std::string name{};

    do
    {
        std::cout << "Enter your name: ";
        std::getline(std::cin, name); // get the entire line, including spaces
    } while (!isValidName(name));

    std::cout << "Hello " << name << "!\n";

    std::cout << "*****************************************************\n";
    return 0;
}