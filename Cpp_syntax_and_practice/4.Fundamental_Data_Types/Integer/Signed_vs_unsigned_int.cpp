#include <iostream>

int main()
{
    // Binary value of following hex is:
    //?   F    F    F    F    F    E    0    0
    //? 1111 1111 1111 1111 1111 1110 0000 0000
    int hex = 0xFFFFFE00;
    std::cout << "Hex = " << std::hex << hex << '\n';
    
    //********** Print hexadecimal as decimal **********
    std::cout << "Hex as Dec = " << std::dec << hex << '\n';

    //********** Convert hexadecimal to decimal **********
    // Signed int contains negative values, so if first digit is 1, int value
    // will be negative
    //  - therefore, -512 will be printed
    int s_dec = hex;
    std::cout << "Signed dec = " << s_dec << '\n';

    // Unsigned int doesn't contain negative values
    unsigned int u_dec = hex;
    std::cout << "Unsigned dec = " << u_dec << '\n';
    
    return 0;
}