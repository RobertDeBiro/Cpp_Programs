#include <iostream>

int main()
{
    char letter{ 'a' };

    //* We can omit any of the for loop statements and expressions
    for( ; letter <= 'z'; )
    {
        std::cout << letter << " = " << static_cast<int>(letter) << '\n';
        ++letter;
    }

    //////////////////////////////////////////////////////////////////

    //* Infinite loops
    int number{};
    
    for(;;)
    {
        std::cout << "Enter a number (enter a zero to exit): ";
        std::cin >> number;
        std::cout << "You entered: " << number << '\n';

        if (number == 0) break;
    }

    return 0;
}