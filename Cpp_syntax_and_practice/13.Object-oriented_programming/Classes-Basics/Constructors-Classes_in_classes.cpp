// In this example we can see that class object is constructed only if object is not a pointer

#include <iostream>

class A
{
public:
    A() { std::cout << "Constructor A\n"; }
    ~A() { std::cout << "Destructor A\n"; }
};

class B
{
public:
    B() { std::cout << "Constructor B\n"; }
    ~B() { std::cout << "Destructor B\n"; }
};

class C
{
public:
    C() { std::cout << "Constructor C\n"; }
    ~C() { std::cout << "Destructor C\n"; }
};

class D
{
public:
    D() { std::cout << "Constructor D\n"; }
    ~D() { std::cout << "Destructor D\n"; }
};

class X
{
public:
    X() { std::cout << "Constructor X\n"; }
    ~X() { std::cout << "Destructor X\n"; }
};

class E
{
private:
    A m_a; // Constructor called
    B* m_b; // Constructor not called
    C* m_c{ nullptr }; // Constructor not called
    D* m_d{ new D }; // Constructor called (new D() calls constructor, not initialization of m_d pointer variable)
    X m_x1; // Constructor called
    X& m_x2{ m_x1 }; // Constructor not called

public:
    // Before constructor is called, constructors of the member variables are called
    E()
    {
        new D; // Constructor called
        std::cout << "Constructor E\n";
    }
    ~E() { std::cout << "Destructor E\n"; }
};

int main()
{
    E e;
    return 0;
} //