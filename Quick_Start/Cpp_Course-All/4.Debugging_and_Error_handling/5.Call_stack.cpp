//* The call stack and call stack window
/**
 * * The call stack
 *      - list of all active functions that have been called to get to the current point of execution
 * 
 * * The call stack window
 *      - debugger window that shows the current call stack
 **/

#include <iostream>

void f1()
{
	std::cout << "f1() called\n";
}

void f2()
{
	std::cout << "f2() called\n";
	f1();
}

int main()
{
    std::cout << "*****************************************************\n";

	f1();
	f2();

    std::cout << "*****************************************************\n";
	return 0;
}
