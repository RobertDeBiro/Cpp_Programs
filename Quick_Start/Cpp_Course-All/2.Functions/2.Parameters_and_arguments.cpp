#include <iostream>

//* Function parameters
/**
 *  - variables used in a function (not defined inside the function, just used)
 *  - always initialized with a value provided by the caller of the function
 *  - example:
 *?     int multiply(int x, int y)
**/
void multiply(int x, int y)
{
    int result = x * y;
    std::cout << "num1 * num2 = " << result << std::endl;
}

int main()
{
    int x = 2;
    int y = 4;

    //* Function arguments
    /**
     *  - value that is passed from the caller to the function when a function call is made
     *  - example:
     *?     multiply(2, 3)
     *  - arguments are "passed by value" to parameters
     *      - when a function is called, all of the parameters of the function are created as variables, 
     *        and the value of each of the arguments is copied into the matching parameter
     *      - argument is essentially just an initializer for the parameter
     **/
    multiply(x, y);

    int z = 3;
    int k = 5;

    multiply(z, k);

    return 0;
}