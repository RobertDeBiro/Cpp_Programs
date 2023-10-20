/*
 * LearnCpp
 * Debugging C++ Programs
 * Summary and quiz
 */

#include <iostream>

int readNumber()
{
	std::cout << "Please enter a number:";
	int x {};
	std::cin >> x;
	return x;
}

void writeAnswer(int x)
{
	std::cout << "The quotient is: " << x << std::endl;
}

int main()
{
    std::cout << "*****************************************************\n";

	int x{ 0 };
	int y{ 0 };
	x = readNumber();
	y = readNumber();
	writeAnswer(x/y);

    std::cout << "*****************************************************\n";
	return 0;
}
