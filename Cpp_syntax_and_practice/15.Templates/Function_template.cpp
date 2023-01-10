#include <iostream>

template <typename T1>
T1 add(T1 x, T1 y)
{
    return x + y;
}

template <typename T2>
T2 mult(T2 x, int y)
{
    return x * y;
}

template <typename T, typename U>
auto sub(T x, U y)
{
    return x - y;
}

int main()
{
	std::cout << add(2, 3) << '\n';
	std::cout << add(1.2, 3.4) << '\n';

    std::cout << "\n";

	std::cout << mult(2, 3) << '\n';
	std::cout << mult(1.2, 3) << '\n';

	std::cout << "\n";

	std::cout << sub(3, 2) << '\n';
	std::cout << sub(3.5, 2) << '\n';
	std::cout << sub(4, 1.5) << '\n';

	return 0;
}
