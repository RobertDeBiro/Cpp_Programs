#include <iostream>

int main()
{
    int x = 5;
    bool y = true;

    bool z = !x;
    bool k = !y;

    std::cout << std::boolalpha;

    std::cout << "z = " << z << '\n';
    std::cout << "k = " << k << '\n';

    z = x && y;
    std::cout << "z = " << z << '\n';

    z = x && k;
    std::cout << "z = " << z << '\n';

    z = x || k;
    std::cout << "z = " << z << '\n';

    std::cout << std::noboolalpha;
    return 0;
}