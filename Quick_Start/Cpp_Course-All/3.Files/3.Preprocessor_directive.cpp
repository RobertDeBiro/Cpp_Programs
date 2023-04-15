//* Preprocessor directives
/**
 *  1. Includes
 *  2. Macro defines
 *  3. Conditional compilation
 **/

//* Includes
/**
 *  - copies contents of the included file into the including file at the point of the #include
 *    directive
 *?     #include <iostream>
 **/

//* Macro defines
/**
 *  - rule that defines how input text is converted into replacement output text
 *  - two types of macro defines directives:
 *      1. Function-like macros
 *          - should be avoided
 *      2. Object-like macros
 *          a) Object-like macros with substitution text
 *?             #define VALUE 20
 *          b) object-like macros without substitution text
 *?             #define NOTHING
 **/

//* Conditional compilation
/**
 *  - allow us to specify under what conditions something will or won't compile
 *  - most used directives:
 *      - ifdef
 *      - ifndef
 *      - endif
 **/

#include <iostream>

#define VALUE 20
#define NAME "John"

int main()
{
    std::cout << NAME << " is " << VALUE << " years old!" << std::endl;

    return 0;
}