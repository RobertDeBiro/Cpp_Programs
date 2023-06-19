//* Global variables
/**
 *  - defined outside of a function
 *  - declared at the top of file, bellow the includes 
 *  - common to use "g_" as a variable name prefix
 *  - file scope (global scope) and static duration
 **/

#include <iostream>
#include <string>

// global variable is automatically zero initialized when declaring it
int g_i;
std::string g_s;

int g_num = 5;

// Constant global variables are not zero initialized by default
// const g_val;

void printNum()
{
    std::cout << "Global number = " << g_num << '\n';
}

int main()
{   
    std::cout << "Global integer = " << g_i << std::endl;
    std::cout << "Global string = " << g_s << std::endl;

    // Global variable is accessible within whole file (file scope)
    std::cout << "Global number = " << g_num << '\n';
    printNum();

    std::cout << "----------------------------------------\n";

    // Local variable will shadow global variable with the same name, but we can still
    // access global variable by using scope resolution operator " :: "
    //  - should be avoided
    int g_num = 10;
    std::cout << "Local number = " << g_num << '\n';
    std::cout << "Global number = " << ::g_num << '\n';

    return 0;
}