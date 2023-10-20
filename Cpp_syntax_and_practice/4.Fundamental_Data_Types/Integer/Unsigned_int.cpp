#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

	//********** Assign negative int to unsigned int **********
	//	- negative number will be converted to positive in a way that
	//	  it will be wrapped
	short i{ -1 };
	unsigned short j = i;
	std::cout << "i = " << i << "; j = " << j << '\n';

	std::cout << "------------------------------\n";

	//********** "Unsigned int" and "signed int" in arithmetic expression **********
	//	- when "unsigned int" and "signed int" are part of arithmetic expression,
	//    "signed int" will be first converted to "unsigned int", and then arithmetic
	//    operation will be evaluated
	unsigned u = 10;
	int iii = 42;
	std::cout << u - iii << std::endl;

    std::cout << "*****************************************************\n";
	return 0;
}
