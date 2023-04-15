/**
 * * Implicit type conversion 
 *      -  C++ compiler can implicitly convert values of one fundamental type to another
 **/
/**
 * * Explicit type conversion - static_cast
 *      - explicitly telling to the compiler to convert a value from one type to another type
 *      - syntax:
 *?       static_cast<new_type_name>(expression)
 *      - doesn't do any range checking - possible overflow (data loss)
 **/

#include <iostream>

void print(double y)
{
	std::cout << "y = " << y << '\n';
}

int main()
{
	int x1{ 5 };
	print(x1);
    std::cout << "x1 = " << x1 << '\n';

	return 0;
}
