#include <iostream>
#include <sstream>

int main()
{
    std::cout << "*****************************************************\n";

    /*
     * Convert numbers to string that will contain those numbers
     */
    std::stringstream os1;

    // Insert numbers into stringstream
    int nValue{ 12345 };
    double dValue{ 67.89 };
    os1 << nValue << ' ' << dValue;

    // Extract stringstream into string objects
    std::string strValue1, strValue2;
    os1 >> strValue1 >> strValue2;

    // Print numbers that are now saved as strings
    std::cout << strValue1 << ' ' << strValue2 << '\n';

    std::cout << "--------------------------\n";

    /*
     * Convert strings that contain some numbers to numbers
     */
    std::stringstream os2;

    // Insert a string of numbers into the stringstream
    os2 << "12345 67.89";

    // Extract stringstream into number objects
    os2 >> nValue >> dValue;

    // Print numbers that are now saved as numbers
    std::cout << nValue << ' ' << dValue << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}