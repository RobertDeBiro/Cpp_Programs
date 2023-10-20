/*
 * LearnCpp
 * Debugging C++ Programs
 * Using an integrated debugger: Watching variables
 */

#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

	int x{ 1 };
	std::cout << x << " ";

	x = x + 2;
	std::cout << x << " ";

	x = x + 3;
	std::cout << x << " ";

    std::cout << '\n';

    std::cout << "*****************************************************\n";
	return 0;
}
