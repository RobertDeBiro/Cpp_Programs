#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

	int x1{};

	//********** Assign char to int **********
	//	- integer can be assigned with character, and conversion from char to int will happen
	//  - this is because char is integral data type
	x1 = 'F';
	std::cout << "F = " << x1 << '\n';


	//********** Assign double to int **********
	//	- when assigning fractional number, fractional part is trimmed
	x1 = 3.7;
	std::cout << "3.7 = " << x1 << '\n';


	//********** Assign negative number to int **********
	//	- signed integer can be negative
	x1 = -3;
	std::cout << "-3 = " << x1 << '\n';


	//********** Assign big number to int **********
	//	- signed integer overflow will result in undefined behavior
	x1 = 3'000'000'000;
	std::cout << "3 000 000 000 = " << x1 << '\n';

    std::cout << "*****************************************************\n";
	return 0;
}
