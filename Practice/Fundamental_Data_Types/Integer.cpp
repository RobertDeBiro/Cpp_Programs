#include <iostream>
#include <cstdint>

void initialization_and_assignment();
void fixed_width_int();
void fast_and_least_int();

int main()
{
	std::cout << "*****************************************************\n";
	
	initialization_and_assignment();
	fixed_width_int();
	fast_and_least_int();

	std::cout << "*****************************************************\n";
	return 0;
}

void initialization_and_assignment()
{
	int x1{};

	// Integer can be assigned with character, and conversion from char to int will happen
	//  - this is because char is integral data type
	x1 = 'F';
	std::cout << "F = " << x1 << '\n';

	// When assigning fractional number, fractional part is cutted
	x1 = 3.7;
	std::cout << "3.7 = " << x1 << '\n';

	// Signed integer can be negative
	x1 = -3;
	std::cout << "-3 = " << x1 << '\n';

	// Output is snipped to the biggest integer value which is: 2 147 483 648 (2^31 - 1)
	x1 = 3'000'000'000;
	std::cout << "3 000 000 000 = " << x1 << '\n';

	std::cout << "------------------------------\n";
}

void fixed_width_int()
{
	// std::uint8_t is considered as a char type by the compiler
    std::uint8_t i{ 70 };
    std::cout << i << std::endl; // F is printed

	std::cout << "------------------------------\n";
}

void fast_and_least_int()
{
	std::cout << "fast 8\t\t: " <<      sizeof(std::int_fast8_t) * 8    << " bits\n";
	std::cout << "fast 16\t\t: " <<     sizeof(std::int_fast16_t) * 8   << " bits\n";
	std::cout << "fast 32\t\t: " <<     sizeof(std::int_fast32_t) * 8   << " bits\n";

	std::cout << "least 8\t\t: " <<     sizeof(std::int_least8_t) * 8   << " bits\n";
	std::cout << "least 16\t: " <<      sizeof(std::int_least16_t) * 8  << " bits\n";
	std::cout << "least 32\t: " <<      sizeof(std::int_least32_t) * 8  << " bits\n";

	std::cout << "------------------------------\n";
}
