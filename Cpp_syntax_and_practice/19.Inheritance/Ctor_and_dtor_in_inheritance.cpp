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
        //* 'this' should be the same as in class 'A'
        std::cout << "B object address: " << this << '\n';
    }
    ~B() { std::cout << "Destructor B\n"; }
};


int main()
{
    std::cout << "*****************************************************\n";

    //* Check order of construction and destruction of base and derived objects
    B b;

    std::cout << "*****************************************************\n";
    return 0;
}
