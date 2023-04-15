#include <iostream>

int main()
{
    int x, y;
    std::cout << "Insert x: ";
    std::cin >> x;
    std::cout << "Insert y: ";
    std::cin >> y;

    std::cout << std::boolalpha;

    bool z = x > y;
    std::cout << "x is bigger than y: " << z << '\n';

    z = (x == y);
    std::cout << "x is equal to y: " << z << '\n';

    z = (x != y);
    std::cout << "x and y are not equal: " << z << '\n';

    std::cout << std::noboolalpha;
    return 0;
}