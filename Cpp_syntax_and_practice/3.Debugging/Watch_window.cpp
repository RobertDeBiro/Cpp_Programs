// LearnCpp
// 3. Debugging C++ Programs
// Using an integrated debugger: Watching variables

#include <iostream>

int main()
{
	int x{ 1 };
	std::cout << x << " ";

	x = x + 2;
	std::cout << x << " ";

	x = x + 3;
	std::cout << x << " ";

	return 0;
}
