#include <iostream>
#include <string>

int main()
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

    return 0;
}
