/*
 * C++ Primer
 * Exercise Section 3.3.3
 *  - Exercise 3.17
 */

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

template <typename T>
void printVector(const T& varVect)
{
    std::cout << "Vector elements: ";
    for(auto elem : varVect)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<std::string> v;
    std::string word;

    // Insert words into vector
    std::cout << "Continuously insert words until you press: \n";
    while(std::cin >> word)
    {
        v.push_back(word);
        if(word == "exit")
            break;
    }
    printVector(v);

    int counter = 0;
    // Loop through words saved inside vector 'v'
    for(auto& w : v)
    {
        // Loop through letters of particular word saved inside string 'w'
        for(auto& c : w)
        {
            c = std::toupper(c);
        }
        std::cout << w << ' ';

        ++counter;
        if(counter % 8 == 0)
            std::cout << '\n';
    }
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}