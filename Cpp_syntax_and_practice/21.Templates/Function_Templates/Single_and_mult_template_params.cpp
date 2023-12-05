#include <iostream>

//********** Function template **********
template <typename T1>
T1 add(T1 x, T1 y)
{
    return x + y;
}

//********** Function template with non-template parameter **********
template <typename T2>
T2 mult(T2 x, int y)
{
    return x * y;
}

//********** Function template with multiple template parameters **********
template <typename T, typename U>
auto sub(T x, U y)
{
    return x - y;
}

int main()
{
    std::cout << "*****************************************************\n";

	std::cout << add<int>(2, 3) << '\n';
	std::cout << add(1.2, 3.4) << '\n'; // Using template argument deduction

    std::cout << "\n";

	std::cout << mult<>(2, 3) << '\n'; // Using template argument deduction
	std::cout << mult<double>(1.2, 3) << '\n';

	std::cout << "\n";

	std::cout << sub(3, 2) << '\n';
	std::cout << sub(3.5, 2) << '\n';
	std::cout << sub(4, 1.5) << '\n';

    std::cout << "*****************************************************\n";
	return 0;
}
