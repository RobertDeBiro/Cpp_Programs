#include <iostream>

int main()
{
    //* Nested if statements
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    //* Dangling else problem
    if (x >= 0) // outer if statement
    {
        if (x <= 20) // inner if statement
        {
            std::cout << x << " is between 0 and 20\n";
        }
        else
        {
            std::cout << x << " is bigger than 20\n";
        }
    }
    else
    {
        std::cout << x << " is negative\n";
    }

    ///////////////////////////////////////////////////////////
    
    //* else-if
    std::cout << "Enter a number: ";
    int a{};
    std::cin >> a;

    if (a < 10)
        std::cout << a << " is smaller than 10\n";
    else if (a > 10)
        std::cout << a << " is bigger than 10\n";
    else
        std::cout << a << " is equal to 10\n";

    return 0;
}