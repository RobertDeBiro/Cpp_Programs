#include <iostream>
#include <bitset>

int main()
{
    std::cout << "*****************************************************\n";
    
    //********** Initialize std::bitset variables **********
    std::bitset<8> bin1{0b1100'0101};   // with 8 bit binary literal
    std::bitset<4> bin2{0b1010};        // with 4 bit binary literal
    std::bitset<8> bin3{0xC5};          // with 8 bit hexadecimal literal

    std::cout << bin1 << '\n';
    std::cout << bin2 << '\n';
    std::cout << "0xC5 = " << bin3 << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
