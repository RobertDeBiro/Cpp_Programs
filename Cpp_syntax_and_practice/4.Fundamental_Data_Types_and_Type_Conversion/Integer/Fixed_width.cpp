#include <iostream>
#include <cstdint>

int main()
{
	// std::uint8_t is considered as a char type by the compiler
    std::uint8_t i{ 70 };
    std::cout << i << std::endl; // F is printed

	return 0;
}
