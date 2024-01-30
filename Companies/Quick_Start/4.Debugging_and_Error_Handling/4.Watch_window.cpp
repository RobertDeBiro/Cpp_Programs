//* Watching variables
/**
 *  - the debugger also lets us watch variables, that is, examine the value of variables as we step
 *    through our code, all without having to modify our code
 *  - we can examine variable value by hovering our mouse over the variable
 **/

//* The watch window
/*
 *  - window where we can add variables that we would like to continually inspect, and these variables
 *    will be updated as we step through our program
 **/

#include <iostream>

// Global variable
int y = 10;

int main()
{
    std::cout << "*****************************************************\n";

    // Local variable
	int x{ 1 };
	std::cout << x << " ";

	x = x + 2;
	std::cout << x << " ";

	x = x + 3;
	std::cout << x << std::endl;

    y = y + x;
    std::cout << y << std::endl;

    std::cout << '\n';

    std::cout << "*****************************************************\n";
	return 0;
}
