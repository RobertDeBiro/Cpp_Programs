// LearnCpp - For-each loops

#include <iostream>
#include <string>

int main()
{
    const std::string names[]{ "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly" };

    std::cout << "Enter a name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name);

    bool found{ false };
    for(const auto& element : names)
    {
        if(element == name)
        {
            found = true;
            break;
        }
    }

    if (found)
        std::cout << name << " was found.\n";
    else
        std::cout << name << " was not found.\n";

    return 0;
}
