#include <iostream>

int main()
{
    int number{};
    
    // while(1)
    while(true)
    {
        std::cout << "Enter a number (enter a zero to exit): ";
        std::cin >> number;
        std::cout << "You entered: " << number << '\n';

        if (number == 0) break; // go out from the loop
    }

    return 0;
}