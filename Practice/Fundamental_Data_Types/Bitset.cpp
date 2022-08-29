#include <iostream>
#include <bitset>

void initialization_and_assignment();
void bitset_functions();

int main()
{
    std::cout << "*****************************************************\n";
    
    initialization_and_assignment();
    bitset_functions();

    std::cout << "*****************************************************\n";
    return 0;
}

void initialization_and_assignment()
{
    // Initialize bitset variable with 8 bit binary literal
    std::bitset<8> bin1{0b1100'0101};
    std::cout << bin1 << '\n';

    // Initialize bitset variable with 4 bit binary literal
    std::bitset<4> bin2{0b1010};
    std::cout << bin2 << '\n';

    // Initialize bitset variable with 8 bit hexadecimal literal
    std::bitset<8> bin3{0xC5};
    std::cout << "0xC5 = " << bin3 << '\n';

    std::cout << "------------------------------\n";
}

void bitset_functions()
{
    std::bitset<8> bin{0b0110'1001};

    std::cout << "Initial bin = " << bin << '\n';

    // test() returns true if the bit value is 1, and false if the value is 0
    std::cout << "1st element: "<< bin.test(0) << '\n';
    std::cout << "2nd element: "<< bin.test(1) << '\n';
    std::cout << "Set 8th element: " << bin.set(7) << '\n';
    std::cout << "Reset 7th element: " << bin.reset(6) << '\n';
    std::cout << "Flip 2nd element: " << bin.flip(1) << '\n';

    std::cout << "------------------------------\n";
}