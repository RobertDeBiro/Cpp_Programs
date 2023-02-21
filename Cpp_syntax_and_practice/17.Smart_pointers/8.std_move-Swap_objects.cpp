#include <iostream>
#include <string>
#include <utility> // std::move

template<class T>
void myswapCopy(T& a, T& b)
{
    T temp{ a };
    a = b;
    b = temp;
}

template<class T>
void myswapMove(T& a, T& b)
{
    T temp{ std::move(a) };
    a = std::move(b);
    b = std::move(temp);
}

int main()
{
    std::cout << "*****************************************************\n";

    std::string x{ "abc" };
	std::string y{ "de" };

	std::cout << "x: " << x << '\n';
	std::cout << "y: " << y << '\n';

	//myswapCopy(x, y);
    myswapMove(x, y);

	std::cout << "x: " << x << '\n';
	std::cout << "y: " << y << '\n';

    std::cout << "*****************************************************\n";
	return 0;
}