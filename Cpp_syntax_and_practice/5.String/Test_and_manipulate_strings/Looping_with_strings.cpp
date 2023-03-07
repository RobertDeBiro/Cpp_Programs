#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    std::cout << "Type string to loop through it and count syllables: ";
    std::string syllables{};
    std::getline(std::cin >> std::ws, syllables);

    int numberOfSyll{ 1 };
    for (const auto& elem : syllables) // string can be looped as an normal array
    {
        if(elem == '-')
            numberOfSyll++;
    }

    std::cout << "Number of syllables in the string: " << numberOfSyll << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
