#include <iostream>

class A
{
public:
    A() { std::cout << "a\n"; }
    ~A() { std::cout << "~a\n"; }
};

class B
{
public:
    B() { std::cout << "b\n"; }
    ~B() { std::cout << "~b\n"; }
};

int main()
{
    std::cout << "*****************************************************\n";

    B b;
    A a; // Object which is last created is first destroyed
    
    std::cout << "*****************************************************\n";
    return 0;
}
