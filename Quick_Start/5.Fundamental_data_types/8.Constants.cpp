//* Constants
/**
 *  - fixed value that cannot be changed 
 *  - C++ has two kinds of constants:
 *      1. Symbolic constants
 *          a) const variables
 *          b) object-like macros with a substitution parameter
 *      2. Literal constants
 *          - every value inserted directly into the code
 *          - example:
 *?             int x = 5
 *                - int - data type
 *                - x - identifier
 *                - 5 - literal
 **/

#include <iostream>

//* Object-like macros with a substitution parameter
/**
 *  - whenever the preprocessor processes this directive, any further occurrence of identifier is
 *    replaced by substitution_text
 *  - has some drawbacks comparing to const variables - const variables preferred
 **/
#define SPEED_OF_LIGHT 186000

int addValues(int a, int b)
{
    return a + b;
}

int main()
{
    //* Const variables
    /**
     *  - to make a variable constant, "const" keyword is used
     *  - must be initialized when defining them
    **/
    const int speed_of_light = 300'000;
    // speed_of_light = 100'000;

    std::cout << "Speed of light [ km/s ] = " << speed_of_light << '\n';
    std::cout << "Speed of light [ miles/s ] = " << SPEED_OF_LIGHT << '\n';

    ////////////////////////////////////////////////////////////

    //* Magic numbers
    /**
     *  - literals in the middle of the code that do not have any context
     *  - should be avoided
     **/
    int result = addValues(5, 6);
    std::cout << "Result = " << result << '\n';

    return 0;
}