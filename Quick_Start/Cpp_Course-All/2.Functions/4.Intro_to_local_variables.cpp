//* Local variables
/**
 *  - function parameters and variables defined inside function body
 *      - function parameters are created and initialized when the function is entered
 *      - variables within the function body are created at the point of definition
 *  - variable properties:
 *      1. Duration (lifetime)
 *      2. Scope
 *      3. Linkage
 **/

//* Local variable lifetime
/** 
 *  - variable lifetime begins - at the point of variable definition
 *  - variable lifetime stops - at the end of the set of curly braces
 *  - runtime property
 **/

//* Local scope
/**
 *  - variable scope begins - at the point of variable definition
 *  - variable scope stops - at the end of the set of curly braces
 *  - compile-time property
 **/

#include <iostream>

int outVar = 10; // global variable

int multiply(int num1, int num2) // num1 and num2 are created and enter scope here
{
    // num1 and num2 are visible/usable within this function only
    int result = num1 * num2 * outVar; // result is created and enter scope here
    ////int result2 = x * num2;
    return result;
} // result, num2 and num1 go out of scope and are destroyed here

int main()
{
    int x = 2; // x is created (lifetime starts), and enters scope here
    int y = 4; // y is created (lifetime starts), and enters scope here

    // x and y are usable within this function only
    
    int result = multiply(x, y); // calls function multiply() with num1=2 and num2=4
    std::cout << x << " * " << y << " = " << result << std::endl;

    return 0;
} // result, y and x go out of scope and are destroyed here