#include <iostream>

class A
{
public:
    A()
    {
        std::cout << "Constructor A\n";
        std::cout << "A object address: " << this << '\n';
    }
    ~A() { std::cout << "Destructor A\n"; }
};

class B : public A
{
public:
    B()
    {
        std::cout << "Constructor B\n";
        std::cout << "B object address: " << this << '\n';
    }
    ~B() { std::cout << "Destructor B\n"; }
};


int main()
{
    std::cout << "*****************************************************\n";

    B b;

    std::cout << "*****************************************************\n";
    return 0;
}
