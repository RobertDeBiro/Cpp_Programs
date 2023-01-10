#include <iostream>

int main()
{
	int x1{};

	// Integer can be assigned with character, and conversion from char to int will happen
	//  - this is because char is integral data type
	x1 = 'F';
	std::cout << "F = " << x1 << '\n';

	// When assigning fractional number, fractional part is trimmed
	x1 = 3.7;
	std::cout << "3.7 = " << x1 << '\n';

	// Signed integer can be negative
	x1 = -3;
	std::cout << "-3 = " << x1 << '\n';

	// Signed integer overflow will result in undefined behavior
	x1 = 3'000'000'000;
	std::cout << "3 000 000 000 = " << x1 << '\n';

	return 0;
}
