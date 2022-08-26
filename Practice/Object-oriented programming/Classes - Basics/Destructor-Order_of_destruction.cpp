#include <iostream>

class A
{
public:
    A() { std::cout << "a"; }
    ~A() { std::cout << "b"; }
};

class B
{
public:
    B() { std::cout << "c"; }
    ~B() { std::cout << "d"; }
};

int main()
{
    B b;
    A a; // Object which is last created is first destroyed
    
    return 0;
}
