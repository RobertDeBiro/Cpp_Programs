/*
 * Stream classes for strings allow us to use the insertions (<<) and extraction (>>)
 * operators to work with strings
 *  - in other words, it functionallity is equal to iostream and ostream classes
 * 
 *  - included in <sstream>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/io/strstream
 */

#include <iostream>
#include <sstream> // stringstream

int main()
{
    std::cout << "*****************************************************\n";

    // Insert into "os1 stringstream object"
    std::stringstream os1;
    os1 << "en garde!\n";

    // Extract "os1" by inserting into "ostream object"
    std::cout << os1.str();

    std::cout << "---------------------------\n";

    // Insert into "os2 stringstream object"
    std::stringstream os2;
    os2.str("en garde!");
    
    // Extract "os1" by inserting into "string objects"
    std::string strValue2a;
    os2 >> strValue2a;
    std::cout << strValue2a << '\n';

    std::string strValue2b;
    os2 >> strValue2b;
    std::cout << strValue2b << '\n';

    os2 >> strValue2b;
    std::cout << strValue2b << '\n';

    os2 >> strValue2b;
    std::cout << strValue2b << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}