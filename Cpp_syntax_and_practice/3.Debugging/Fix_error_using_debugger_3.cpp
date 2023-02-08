// LearnCpp
// Debugging C++ Programs
// Summary and quiz

#include <iostream>

void d()
{ // here
}

void c()
{
}

void b()
{
	c();
	d();
}

void a()
{
	b();
}

int main()
{
    std::cout << "*****************************************************\n";

	a();

    std::cout << "*****************************************************\n";
	return 0;
}
