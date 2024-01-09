#include <iostream>

int main()
{
    //* Data, object and value
    /**
     * * Data
     *      - program is available to contain and save some data
     *      - a program can acquire data to work with in many ways:
     *          - from a file
     *          - from a database
     *          - over a network
     *          - from the user providing input on a keyboard
     *          - from the programmer putting data directly into the source code of the program itself
     *      - stored in RAM (Random Access Memory) while program is running
     *          - temporary memory
     *          - program can quickly work with the data (read and write) present in RAM
     * 
     * * Object and value:
     *      - value = particular data stored in memory
     *      - object = memory chunk that holds particular data
     *      => object has value
     **/

    std::cout << 'a' << std::endl;
    std::cout << 73 << std::endl;
    std::cout << 12.3 << std::endl;

    //* Variable
    /**
     *  - named object
     **/
    x = 'a';
    y = 73;
    z = 12.3;

    //* Data type:
    /**
     *  - fundamental (built-in) data types:
     *      - integer
     *          - int
     *          - number without decimal point
     *      - floating-point
     *          - e.g float, number
     *          - number with decimal point
     *      - character (char)
     *          - charactes such as letters
     *      - boolean (bool)
     *          - true or false
     *  - user-defined data types
     **/

    char x = 'a';
    int y = 73;
    double z = 12.3;

    //* Variable definition
    /**
     *  - definition is special kind of declaration statement used for creating a variable
     *  - defining one variabe:
     *?     int x;
     *  - defining multiple variables:
     *?     int x, y;
     *      - two common mistakes:
     *?         1) int a, int b;
     *?         2) int a, double b;
     **/
    std::cout << "x = " << x << std::endl;
    ////int a, int b;
    int a;
    int b;

    //* Variable assignment
    /**
     *  - after we define a variable we can assign a value to it – that process is called copy assignment
     *    (or just assignment)
     *  - assignment operator: =
     *  - downside - requires at least two statements:
     *      1. Define the variable
     *      2. Assign the value
     **/
    a = 5;
    b = 5.5;

    //* Variable initialization
    /**
     *  - initialization - defining variable and assigning value to it, in one statement
     *  - three types of variable initialization:
     *      1. Copy initialization
     *?        int a = 5
     *      2. Direct initialization
     *?        int a( 5 )
     *      3. Uniform initialization
     *?        int a{ 5 }
     *          - can be used for all types
     *          - offers zero initialization
     *          - disallows "narrowing" type conversion
     * - we can initialize multiple variables in one statement 
     * - uninitialized variable
     *      - if we don't give a variable some value variable will have whatever value is in memory 
     *        location which is given to the variable by the compiler
     *      – that value is called garbage value and that variable is uninitialized variable
     *      - avoid having uninitialized variables!
     **/
    int x2 = 1;      // Copy initialization
    int y2( 2 );     // Direct initialization
    int z2a{ 3 };    // Uniform initialization
    int z2b{ };      // Zero initialization (using uniform initialization syntax)

    // Copy and direct initializations allows "narrowing" type conversion
    int x4 = 3.4;
    int y4( 3.4 );
    std::cout << "x4 = " << x4 << std::endl;
    std::cout << "y4 = " << y4 << std::endl;

    ////int z5{ 3.4 };

    // Initializing multiple variables
    int a1 = 5, b1 = 6;
	int a2( 5 ), b2( 6 );
    int a3{ 5 }, b3{ 6 };

    //* Literals
    /**
     *  - literal (also known as literal constant) is a fixed value that has been inserted directly
     *    into the source code
     *  - literals and variables both have a value (and a type), but the value of a literal is fixed
     *    and can't be changed
     **/

    return 0;
}