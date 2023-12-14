#include <iostream>
#include <string>
#include <map>

void printMultimap(const std::multimap<char, int>& varMultimap)
{
    for (const auto& [key, value] : varMultimap) {
        std::cout << '[' << key << "] = " << value << "; ";
    }
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::multimap<char, int> varMultimap { {'a', 5}, {'b', 7}, {'a', 12}, {'b', 9} };
    std::cout << "Initial multimap: ";
    printMultimap(varMultimap);

    //* Find pair that contains required key
    //  - I have found information on the internet that it is not defined which pair will '.find()'
    //    return, but in this example it always return first pair that contains 'a'
    //  - find pair 10 times in order to test which pair will be returned
    for(int i = 1; i<= 10; ++i)
    {
        auto pair{ varMultimap.find('a') };
        std::cout << "Found pair that contains 'a': " << '[' << pair->first
                  << "] = " << pair->second << "\n";
    }

    std::cout << "*****************************************************\n";
    return 0;
}
