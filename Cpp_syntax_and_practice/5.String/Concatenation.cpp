#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    // Strings concatenation only works with std::string type, or by using append() member function
    std::string string1{"Hello"};
    std::string string2{"World!"};
    std::string concat1 = string1 + string2;
    std::cout << "Concatenated string 1: " << concat1 << '\n';

    std::string concat2{"Hello"};
    concat2 += static_cast<std::string>("Croatia!");
    std::cout << "Concatenated string 2: " << concat2 << '\n';

    // Concatenate using append function
    std::string concat3{"Hello"};
    concat3.append("Zagreb!");
    std::cout << "Concatenated string 3: " << concat3 << '\n';

    /*
     * Following code won't work since string literals, i.e const char variables, are trying to be added
     */
    // std::string concat1{};
    // concat1 = "Hello" + "World!";
    // std::cout << "Concatenated string 1: " << concat1 << '\n';

    /*
     * Note
     *  - C++ doesn't support multiplication of string and integer, for example:
     *    std::string stringM{"Hello"};
     *    std::string mult = stringM * 3;
     *    
     *    => wanted printout: HelloHelloHello
     */

    std::cout << "*****************************************************\n";
    return 0;
}
