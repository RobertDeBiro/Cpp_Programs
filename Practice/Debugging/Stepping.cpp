// Using an integrated debugger: Stepping

#include <iostream>

void printValue(int value)
{
    std::cout << value << '\n';
}

int main()
{
    int x(5);
    printValue(5);
    printValue(6);
    printValue(7);
    std::cout << "x is " << x << "\n";

    return 0;
}
