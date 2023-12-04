//* Class object is constructed only if object is not a pointer or reference

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
private:
    A m_a_1; // Constructor called
    A& m_a_2{ m_a_1 }; // Constructor not called
    B* m_b_1; // Constructor not called
    B* m_b_2{ nullptr }; // Constructor not called
    B* m_b_3{ new B }; // Constructor called (new B() calls constructor)

public:
    // Before constructor is called, constructors of the member variables are called
    C() { std::cout << "Constructor C\n"; }
    ~C() { std::cout << "Destructor C\n"; }
};

int main()
{
    std::cout << "*****************************************************\n";

    C c;

    std::cout << "*****************************************************\n";
    return 0;
} //