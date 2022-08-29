#include <iostream>

int main()
{
    double zero {0.0};
    double posinf { 5.0 / zero };
    std::cout << "positive infinity = " << posinf << '\n';

    double neginf { -5.0 / zero };
    std::cout << "negative infinity = " << neginf << '\n';

    double nan { zero / zero }; // not a number (mathematically invalid)
    std::cout << "not a number = " << nan << '\n';

    int x{};

    // When division by zero is saved inside double variable we will have posinf/neginf
    double y{ 12.0 / x };
	std::cout << "12 / " << x << " = " << y << '\n';

    // When division by zero is saved inside int variable we will have arithmetic exception
    int z{ 12 / x };
	std::cout << "12 / " << x << " = " << z << '\n';

    return 0;
}
