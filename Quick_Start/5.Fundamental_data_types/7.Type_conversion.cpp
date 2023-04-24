#include <iostream>

void print_d(double y)
{
	std::cout << "y = " << y << '\n';
}

// When assigning fractional number to integer variable, fractional part is trimmed
void print_i(int y)
{
	std::cout << "y = " << y << '\n';
}

int main()
{
    //* Implicit type conversion
    /**
     *  -  C++ compiler can implicitly convert values of one fundamental type to another
     **/
	int x1{ 5 };
	print_d(x1);
    std::cout << "x1 = " << x1 << '\n';

    double x2{ 5.5 };
	print_i(x2);
    std::cout << "x2 = " << x2 << '\n';

    //* Explicit type conversion
    /**
     *  - explicitly telling to the compiler to convert a value from one type to another type
     *  - syntax:
     *?     static_cast<new_type_name>(expression)
     *  - doesn't do any range checking - possible overflow (data loss)
     **/
    char c = 65;
    std::cout << "Character c = " << c << '\n';
    std::cout << "Integer c = " << static_cast<int>(c) << '\n';

	return 0;
}
