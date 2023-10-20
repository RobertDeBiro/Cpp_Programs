/*
 * LearnCpp
 * Debugging C++ Programs
 * Using an integrated debugger: The call stack
 */

#include <iostream>

void a()
{
	std::cout << "a() called\n";
}

void b()
{
	std::cout << "b() called\n";
	a();
}

int main()
{
    std::cout << "*****************************************************\n";

	a();
	b();

    std::cout << "*****************************************************\n";
	return 0;
}
