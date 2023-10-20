#include <iostream>
#include <cstdint>

int main()
{
    std::cout << "*****************************************************\n";

	//********** Check the size of "fast" and "least" on this machine **********
	std::cout << "fast 8\t\t: " <<      sizeof(std::int_fast8_t) * 8    << " bits\n";
	std::cout << "fast 16\t\t: " <<     sizeof(std::int_fast16_t) * 8   << " bits\n";
	std::cout << "fast 32\t\t: " <<     sizeof(std::int_fast32_t) * 8   << " bits\n";

	std::cout << "least 8\t\t: " <<     sizeof(std::int_least8_t) * 8   << " bits\n";
	std::cout << "least 16\t: " <<      sizeof(std::int_least16_t) * 8  << " bits\n";
	std::cout << "least 32\t: " <<      sizeof(std::int_least32_t) * 8  << " bits\n";

    std::cout << "*****************************************************\n";
	return 0;
}
