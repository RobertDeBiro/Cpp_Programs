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

//* Switch-case - Return
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
            // In this example this won't happen, but always good to have
            std::cout << "Error - undefined mathematical operation!" << '\n';
            return 0;
    }
}

//* Switch-case - Break
/*
int calculate(int x, int y, char op)
{
    int result{};

    switch(op)
    {
        case '+':
            result = x + y;
            //break;
        case '-':
            result x - y;
            //break;
        case '*':
            result x * y;
            //break;
        case '/':
            result x / y;
            //break;
        case '%':
            result x % y;
            //break;
        default:
            // In this example this won't happen, but always good to have
            std::cout << "Error - undefined mathematical operation!" << '\n';
            result = 0;
            //break;
    }

    return result;
}
*/

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
