//* Computer program
/**
 *  - a computer program is a sequence of instructions that tell the computer what to do
 *  - by far the most common type of instruction is called statement
 *  - a statement is a type of instruction that causes the program to perform some action
 *  - instruction - tells to computer what to do
 *  - statement - tells to program what to do
 **/

//* Functions:
/**
 *  - collection of statements that get executed sequentially (in order, from top to bottom)
 *  - written to do a specific job, to execute some functionallity
 *  - contains:
 *      - function header
 *          - function name
 *          - return type
 *          - input parameters (optionally)
 *      - function body
 *          - using curly braces it encapsulates statements that are considered part of the function
 **/

//* Pseudo computer program example:
/**
 *      instruction_1 - include some library to our program
 * 
 *?     <return_type> <function1_name> (<input_parameters>)
 *?     {
 *          statement_1 - open and read from file
 *          statement_2 - add two numbers
 *          statement_3 - write text to a terminal
 *?     }
 *
 *?     <return_type> <function2_name> (<input_parameters>)
 *?     {
 *          statement_1 - open and read from file
 *          statement_2 - multiply two numbers
 *          statement_3 - write text to a terminal
 *?     }
 **/

//* 1.Level of comment - What is the code goal
// Program prints "Hello World!" to the terminal

//* Preprocesor directive
/**
 *  - not a statement
 *  - causes preprocessor program to perform some actions
 *  - called by using "#" (hash) symbol
 **/
#include <iostream>

//* main() function:
/**
 *  - every C++ program must have a special function with following characterictics:
 *      - function name: main
 *      - input parameters: none
 *      - return type: integer value
 *          - caller of the main() function is operating system
 *  - when a program is run, execution starts with the first statement insite the main() function
 **/
int main()
{
//* 2. Level of comment - how the code is going to accomplish the goal
// "Hello World!" will be printed by using cout object from iostream library

    //* Level of comment - Why the code is doing this to accomplish it's goal
    // cout object prints the text to the terminal
    std::cout << "Hello World!" << std::endl;

    return 0; // Return value 0, which indicates that main() finished sucessfully
}