/*
 * LearnCpp
 * Debugging C++ Programs
 * Summary and quiz
 */

#include <iostream>

int readNumber(int x)
{
	std::cout << "Please enter a number: ";
	std::cin >> x;
	return x;
}

void writeAnswer(int x)
{
	std::cout << "The sum is: " << x << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

	int x {};
	readNumber(x);
	x = x + readNumber(x);
	writeAnswer(x);

    std::cout << "*****************************************************\n";
	return 0;
}
