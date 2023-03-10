#include <iostream>
#include <cctype>

int main()
{
    std::cout << "*****************************************************\n";

    std::string word{ "hello world!" };

    for(auto& c : word)
    {
        c = std::toupper(c);
    }
    std::cout << word << '\n';

    for(auto& c : word)
    {
        c = std::tolower(c);
    }
    std::cout << word << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}