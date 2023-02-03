#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    std::cout << "Continuously enter integer numbers to sum: ";
    int num, sum;
    
    // In order to go out from the loop we must enter:
    //  1. Ctrl + Z
    //  2. Enter
    while (std::cin >> num)
        sum += num;
    std::cout << "Final sum: " << sum << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}