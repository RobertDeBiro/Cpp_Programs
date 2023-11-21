#include <iostream>
#include <bitset>

int main()
{
    std::cout << "*****************************************************\n";
    
    std::bitset<8> bin{0b0010'1101};

    std::cout << "Initial bin = " << bin << '\n';

    // test() returns true if the bit value is 1, and false if the value is 0
    std::cout << "1st element: "<< bin.test(0) << '\n';
    std::cout << "2nd element: "<< bin.test(1) << '\n';
    std::cout << "Set 2nd element: " << bin.set(1) << '\n';
    std::cout << "Reset 6st element: " << bin.reset(5) << '\n';
    std::cout << "Flip 3rd element: " << bin.flip(2) << '\n';
    std::cout << "Is any of the bits true: " << std::boolalpha << bin.any() << std::noboolalpha << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
