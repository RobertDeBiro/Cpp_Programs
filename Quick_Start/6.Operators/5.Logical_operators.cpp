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

    //* Short circuit evaluation
    /**
     *  - behavior when logical AND and logical OR operators evaluate only one expression,
     *    primarily for optimization purposes
     *      - if first expression is false, AND immediatelly returns false
     *      - if first expression is true, OR immediatelly returns true
     **/
    z = x || (std::cout << "Hello!\n");
    z = x && (std::cout << "Hello!\n");

    std::cout << std::noboolalpha;
    return 0;
}