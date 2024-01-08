/*
 * Stream classes for strings allow us to use the insertions (<<) and extraction (>>)
 * operators to work with strings
 *  - in other words, it functionallity is equal to 'iostream' and 'ostream' classes
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/io/strstream
 */

#include <iostream>
#include <sstream> // stringstream

int main()
{
    std::cout << "*****************************************************\n";

    // Insert into 'os1 stringstream' object
    std::stringstream os1;
    os1 << "en garde!\n";

    //* Extract 'os1' by inserting into 'ostream' object
    std::cout << os1.str();

    std::cout << "---------------------------\n";

    // Insert into 'os2 stringstream' object
    std::stringstream os2;
    os2.str("en garde!");
    
    //* Extract 'os2' by inserting into 'std::string' object
    //  - when 'std::string' object is used for extraction from 'stringstream', it is extracted word by word
    std::string strValue2a;
    os2 >> strValue2a;
    std::cout << strValue2a << '\n';

    std::string strValue2b;
    os2 >> strValue2b;
    std::cout << strValue2b << '\n';

    // Data sent from 'stringstream' object won't be present in that object anymore
    std::string strValue2c;
    os2 >> strValue2c;
    std::cout << strValue2c << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}