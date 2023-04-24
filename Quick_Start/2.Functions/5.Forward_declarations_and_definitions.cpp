//* Forward declaration
/**
 *  - tells the compiler about the existence of an identifier (function, variable..) and its type
 *  - function prototype
 *      - declaration statement used for writing function declaration
 *      - consists of:
 *          - function's name
 *          - function's return type
 *          - parameters
 *          - semicolon at the end
 **/

//* Declaration vs. Definition
/**
 *  - definition:
 *      - implements (for functions or types) or instantiates (for variables) the identifier
 *      - needed to satisfy the linker
 *      - all definitions also serve as a declarations
 *  - declarations:
 *      - statement that tells the compiler about the existence of an identifier and its type 
 *        information
 *      - needed to satisfy the compiler
 *      - pure declarations
 **/

//* One Definition Rule (ODR)
/**
 *  - within a given file:
 *      - a function, object, type, or template can only have one definition
 *  - within a given program:
 *      - a normal function or an object can only have one definition
 *      - a type, template function, and inline function and variables can have multiple definitions so
 *        long as they are identical
 **/

#include <iostream>

void funct2();
void funct1();
int multiply(int x, int y);

void funct2()
{
    funct1();
}

void funct1()
{
    funct2();
}

int main()
{
    int x = 1, y = 2;
    int result = multiply(x, y);

    return 0;
}

int multiply(int x, int y)
{
    int result = x + y;
    return result;
}