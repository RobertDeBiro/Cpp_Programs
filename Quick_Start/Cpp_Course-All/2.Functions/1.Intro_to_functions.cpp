/**
 * * Introduction to functions:
 *      - provide a way to split our programs into small, modular chunks that are easier to organize, test, 
 *        and use
 *      - written to do a specific job, to execute some functionality
 *      - reusable
 *      - the function initiating the function call is the caller, and the function being called is the
 *        called function
 *      - we cannot define one function inside other function
 **/

#include <iostream>

void sayHi()
{
    std::cout << "Hi!" << std::endl;
}

void good_job()
{
    std::cout << "Good job!" << std::endl;
    sayHi();
}

int main()
{
    std::cout << "Starting main()" << std::endl;

    // ...
    // Some code here
    sayHi();
    
    // ...
    // Some code here
    sayHi();

    // ...
    // Some code here
    good_job();

    std::cout << "Ending main()" << std::endl;

    //! SYNTAX ERROR: We cannot define function inside other function!
    // void funct()
    // {
    //     std::cout << "I am inside defined inside main()!" << std::endl;
    // }

    return 0;
}