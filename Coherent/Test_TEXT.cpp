#include <iostream>
#include <iomanip> // std::setprecision()

int main()
{
    float f1 = 4595315.01234f;
    float f2 = 4595315;
    float f3 = 4595315.01f;

    std::cout << "Float f1 = " << f1 << '\n';
    std::cout << "Float f2 = " << f2 << '\n';
    std::cout << "Float f3 = " << f3 << '\n';

    std::cout << "--------------------------------------\n";

    std::cout << std::setprecision(7);

    std::cout << "Float f1 = " << f1 << '\n';
    std::cout << "Float f2 = " << f2 << '\n';
    std::cout << "Float f3 = " << f3 << '\n';

    return 0;
}