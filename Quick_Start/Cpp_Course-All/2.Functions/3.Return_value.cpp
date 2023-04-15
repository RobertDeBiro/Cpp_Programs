#include <iostream>

//* Function return value
/**
 *  - to return a value back to the caller two things are needed
 *      1. Return type
 *          - indicates the type of value that will be returned from function
 *      2. Return value
 *          - only if return type is not void
 *  - if function shouldn't return value, return type must be void
 *  - "return by value":
 *      - when the return statement is executed, the function exits immediately, and the return value 
 *        is copied from the function back to the caller
 **/
int multiply(int num1, int num2)
{
    int result = num1 * num2;

    return result;

    int result2 = num1 + num2;

    return result2;
}

int main()
{
    int x = 2;
    int y = 4;

    std::cout << x << " * " << y << " = " << multiply(x, y) << std::endl;
    
    int result = multiply(x, y);
    std::cout << x << " * " << y << " = " << result << std::endl;

    multiply(x, y);

    return 0;
}