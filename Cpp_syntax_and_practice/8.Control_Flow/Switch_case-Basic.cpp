// LearnCpp
// 7. Control Flow and Error Handling
// Switch fallthrough and scoping

#include <iostream>

int calculate(int x, int y, char op)
{
    switch(op)
    {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
        case '%':
            return x % y;
        default:
            std::cout << "Error - undefined mathematical operation!" << '\n';
            return 0;
    }
}

int main()
{
    std::cout << "Enter first integer, x = ";
    int x{};
    std::cin >> x;

    std::cout << "Enter second integer, y = ";
    int y{};
    std::cin >> y;

    std::cout << "Enter mathematical operation you want to do on those integers: ";
    char op{};
    std::cin >> op;

    std::cout << "x " << op << " y = " << calculate(x, y, op) << '\n';

    return 0;
}
