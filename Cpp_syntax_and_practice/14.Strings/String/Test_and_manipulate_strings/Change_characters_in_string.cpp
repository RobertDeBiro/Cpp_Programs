/*
 * C++ Primer
 * Exercises section 3.2.3
 *  - Exercise 3.6
 *  - Exercise 3.8
 */

#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    std::string s{ "Some string" };
    std::cout << "Initial string:\t" << s << '\n';

    // Using "Range for" loop to change the string
    for(auto& c : s)
        c = 'X';
    std::cout << "Range for:\t" << s << '\n';

    std::cout << "----------------------------------------\n";

    // Using "While" loop to change the string and null terminator as termination indicator
    int i = 0;
    while(s[i] != '\0')
    {
        s[i] = 'Y';
        i++;
    }
    std::cout << "While:\t\t" << s << '\n';

    // ERROR: string doesn't decay to a pointer like a fixed array does, since string is actually
    //        not array but rather an object
    // while(*(s + i) != '\0')

    std::cout << "----------------------------------------\n";

    // Using "For" loop to change the string and 'length()' as termination indicator
    //  - 's.length()' doesn't contain '\0'
    for(int i = 0; i <= static_cast<int>(s.length()); i++)
        s[i] = 'Z';
    std::cout << "For:\t\t" << s << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}