#include <iostream>

int main()
{
    int number;

    // std::cout << "Enter a number (enter a zero to exit): ";
    // std::cin >> number;
    // std::cout << "You entered: " << number << '\n';

    while (number != 0)
    {
        std::cout << "Enter a number (enter a zero to exit): ";
        std::cin >> number;
        std::cout << "You entered: " << number << '\n';
    }

    return 0;
}