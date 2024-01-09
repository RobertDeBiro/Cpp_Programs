//* Stepping and stepping options
/**
 * * Stepping
 *      - name for a set of related debugger features that let us execute (step through) our code statement
 *        by statement
 * 
 * * Stepping options
 *      1. Step into
 *      2. Step over
 *      3. Step out
 *      4. Continue
 *      5. Restart
 *  	6. Stop 
 **/

//* Breakpoints and run/jump to cursor
/**
 * * Breakpoints
 *      - special marker that tells the debugger to stop execution of the program on that marker when
 *        running in debug mode
 *      - several options:
 *          - toogle (disable) breakpoint
 *          - remove breakpoint
 *          - edit breakpoint
 * 
 * * Run to cursor
 *      - executes the code until code reaches the statement where the mouse cursor is placed
 * 
 * * Jump to cursor
 *      - skips execution of some part of the code
 **/

#include <iostream>

void printValue(int value)
{
    std::cout << value << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    printValue(5);
    printValue(6);
    printValue(7);

    std::cout << "*****************************************************\n";
    return 0;
}
