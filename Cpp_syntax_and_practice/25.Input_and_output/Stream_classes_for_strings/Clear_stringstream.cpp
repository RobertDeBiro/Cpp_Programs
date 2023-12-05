/*
 *  - in order to reuse stringstream object that we previously already used, we need to clear it first
 *  - we can clear it by adding either empty C-style string or std::string into stringstream str() function
 *  - when clearing out a stringstream, it is also generally a good idea to call the clear() function
 *      - clear() resets any error flags that may have been set and returns the stream back to the ok state
 */

#include <iostream>
#include <sstream>

int main()
{
    std::cout << "*****************************************************\n";

    // Initial stringstream
    std::stringstream os;
    os << "Hello!\n";
    std::cout << os.str();

    std::cout << "-------------------------\n";

    // Clear the stringstream by adding empty C-style string to str()
    os.str("");
    os.clear();

    // Reuse os stringstream
    os << "World!\n";
    std::cout << os.str();

    std::cout << "-------------------------\n";

    // Clear the stringstream by adding empty string to str()
    os.str(std::string{});
    os.clear();

    os << "Europe!\n";
    std::cout << os.str();

    std::cout << "*****************************************************\n";
    return 0;
}