#include <iostream>

int main()
{
	short i{ -1 };
	unsigned short j = unsigned(i);
	std::cout << "i = " << i << "; j = " << j << '\n';

	std::cout << "------------------------------\n";

	unsigned u = 10;
	int iii = 42;

	// When "unsigned int" and "int" are part of arithmetic expression,
	// "int" will be first converted to "unsigned int", and then arithmetic
	// operation will be evaluated
	std::cout << u - iii << std::endl;

	return 0;
}
