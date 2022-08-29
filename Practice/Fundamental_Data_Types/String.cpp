#include <iostream>
#include <string> // std::getline

void initialization_and_assignment();
void getline();
void length();
void replace();
void looping();

int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();
    getline();
    length();
    replace();
    looping();

    std::cout << "*****************************************************\n";
    return 0;
}

void initialization_and_assignment()
{
    // Initialize string variable with empty string
    std::string str1{};
    std::cout << "String initialized with empty string: " << str1 << '\n';

    // std::string is dynamically resized for the string we need
    std::string str2{ "I saw a red car yesterday." };
    std::cout << str2 << '\n';

    str2 = "I saw a blue car yesterday.";
    std::cout << str2 << '\n';

    str2 = "I saw blue, red, green and yellow cars yesterday.";
    std::cout << str2 << '\n';

    std::cout << "------------------------------\n";
}

void getline()
{
    std::cout << "Enter your full name: ";
    std::string fullName;
    // the std::ws input manipulator tells std::cin to ignore any leading whitespace
    // that may be left from previous std::cin inputs
    std::getline(std::cin >> std::ws, fullName);

    std::cout << "Fullname = " << fullName << '\n';

    std::cout << "------------------------------\n";
}

void length()
{
    std::cout << "Enter some string to check its length: ";
    std::string str;
    std::getline(std::cin >> std::ws, str);

    std::cout << "String " << str << " has length of " << str.length() << " characters!\n";

    std::cout << "------------------------------\n";
}

void replace()
{
    std::string str{ "I saw a red car yesterday." };
    std::cout << str << '\n';

    // Replace 3 characters with new string, starting from index 8 (9. element)
    str.replace(8, 3, "blue");
    std::cout << str << '\n';

    std::cout << "------------------------------\n";
}

void looping()
{
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
}