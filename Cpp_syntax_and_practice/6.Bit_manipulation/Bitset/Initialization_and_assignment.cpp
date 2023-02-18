#include <iostream>
#include <bitset>

int main()
{
    std::cout << "*****************************************************\n";
    
    // Initialize bitset variable with 8 bit binary literal
    std::bitset<8> bin1{0b1100'0101};
    std::cout << bin1 << '\n';

    // Initialize bitset variable with 4 bit binary literal
    std::bitset<4> bin2{0b1010};
    std::cout << bin2 << '\n';

    // Initialize bitset variable with 8 bit hexadecimal literal
    std::bitset<8> bin3{0xC5};
    std::cout << "0xC5 = " << bin3 << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
