// LearnCpp
// Control Flow and Error Handling
// Switch fallthrough and scoping

#include <iostream>

int getInteger()
{
    std::cout << "Please, enter integer: ";
    int x;
    std::cin >> x;
    return x;
}

char getOperation()
{
    char op;
    do
    {
        std::cout << "Enter an operation ('+', '-', '*', '/'): ";
        std::cin >> op;
    }
    while (op!='+' && op!='-' && op!='*' && op!='/');

    return op;
}

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
    std::cout << "*****************************************************\n";

    int x{ getInteger() };
    int y{ getInteger() };
    char op{ getOperation() };

    std::cout << "x " << op << " y = " << calculate(x, y, op) << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
