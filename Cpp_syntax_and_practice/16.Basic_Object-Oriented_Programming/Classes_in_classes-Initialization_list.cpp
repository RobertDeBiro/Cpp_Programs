#include <iostream>

class A
{
    int m_a1{};
    int m_a2{};

public:
    A(int a1, int a2) : m_a1{ a1 }, m_a2{ a2 }
    {
        std::cout << "A constructor called\n";
        std::cout << "m_a1 = " << m_a1 << "; m_a2 = " << m_a2 << '\n';
    }
};

class B
{
    int m_b1{};
    int m_b2{};

public:
    B(int b1, int b2) : m_b1{ b1 }, m_b2{ b2 }
    {
        std::cout << "B constructor called\n";
        std::cout << "m_b1 = " << m_b1 << "; m_b2 = " << m_b2 << '\n';
    }
};

class C
{
    A m_a;
    B m_b;

public:
    C(A a, B b) : m_a{ a }, m_b{ b }
    {
        std::cout << "C constructor called\n";
    }
};

int main()
{
    std::cout << "*****************************************************\n";

    //* Class can initialize class member variables using initialization list
    C c
    {
        {1, 2},
        {3, 4}
    };

    std::cout << "*****************************************************\n";
    return 0;
}