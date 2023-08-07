#include <iostream>
#include "../inc/add.hpp"
#include "../inc/multiply.hpp"

int main()
{
	int i = 5;
    int j = 10;

    int a = add(i, j);
    int m = multiply(i, j);

    std::cout << "a = " << a << std::endl;
    std::cout << "m = " << m << std::endl;

	return 0;
}