/*
 * LearnCpp
 * Bit manipulation
 * Bitwise operators
 */

#include <iostream>
#include <bitset>

// "rotl" stands for "rotate left"
std::bitset<4> rotl(std::bitset<4> bits)
{
    const bool firstBit{ bits.test(3) };
    bits <<= 1;

    if(firstBit)
        bits.set(0);

    return bits;
}

/* Solution 2
std::bitset<4> rotl(std::bitset<4> bits)
{
    const bool firstBit{ bits.test(3) };
    std::bitset<4> rotlBits{ bits << 1 };

    if(firstBit)
        rotlBits |= 0b0001;

    return rotlBits;
}
*/

int main()
{
    std::cout << "*****************************************************\n";

    std::bitset<4> bits1{ 0b0001 };
    std::cout << rotl(bits1) << '\n';

    std::bitset<4> bits2{ 0b1001 };
    std::cout << rotl(bits2) << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
