// LearnCpp
// This program, in which we are using function pointers, is actually replacement for
// 8. Control Flow and Error Handling :: Switch-case_math_operations.cpp
// - this program is larger than the other one, but if the function would be much bigger, this is the proper way to implement the solution

#include <iostream>
#include <functional> // std::function

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

int add(int x, int y)
{
  return x + y;
}

int subtract(int x, int y)
{
  return x - y;
}

int multiply(int x, int y)
{
  return x * y;
}

int divide(int x, int y)
{
  return x / y;
}

using arithmeticFcn = std::function<int(int, int)>;

arithmeticFcn getArithmeticFunction(char op)
{
  switch(op)
  {
      default: //default will be to add
      case '+': return add;
      case '-': return subtract;
      case '*': return multiply;
      case '/': return divide;
  }
}

int main()
{
    int x{ getInteger() };
    int y{ getInteger() };
    char op{ getOperation() };

    arithmeticFcn fcnPtr{ getArithmeticFunction(op) };
    std::cout << x << ' ' << op << ' ' << y << " = " << fcnPtr(x, y) << '\n';

    return 0;
}
