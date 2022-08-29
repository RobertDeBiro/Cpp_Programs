#include <iostream>

class DefCon
{
    DefCon()
    {
        std::cout << "Default constructor without default parameter is called!\n";
    }

    DefCon(int a = 0)
    {
        std::cout << "Default constructor with default parameter is called!\n";
    }
};

int main()
{
    // 1. Example
    //     - doesn't compile, causes error due to ambiguity
    //DefCon a;

    // 2. Example
    //     - compiles, but it doesn't call constructor
    //     - the same would be if we would declare, for example, only integer variable (int a)
    DefCon a();

    return 0;
}
