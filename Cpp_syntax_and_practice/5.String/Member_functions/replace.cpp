#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    std::string str{ "I saw a red car yesterday." };
    std::cout << str << '\n';

    // Replace 3 characters with new string, starting from index 8 (9. element)
    str.replace(8, 3, "blue");
    std::cout << str << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
