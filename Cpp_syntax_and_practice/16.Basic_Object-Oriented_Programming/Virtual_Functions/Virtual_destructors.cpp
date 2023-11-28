#include <iostream>

class A
{
public:
    ~A() // note: NOT virtual
    {
        std::cout << "Calling ~A()\n";
    }
};

class B: public A
{
private:
    int* m_array;

public:
    B(int length)
      : m_array{ new int[length] }
    {
    }

    virtual ~B()
    {
        std::cout << "Calling ~B()\n";
        delete[] m_array;
    }
};

class C: public B
{
private:
    int* m_array;

public:
    C(int length1, int length2)
      : B(length1), m_array{ new int[length2] }
    {
    }

    ~C()
    {
        std::cout << "Calling ~C()\n";
        delete[] m_array;
    }
};

int main()
{
    std::cout << "*****************************************************\n";

    B* b1 { new B(1) };
    A* a { b1 };

    std::cout << "Delete a:\n";
    delete a;

    std::cout << "--------------------------------\n";

    C* c { new C(2, 3) };
    B* b2 { c };

    std::cout << "Delete b2:\n";
    delete b2;

    std::cout << "Program finished!\n";

    std::cout << "*****************************************************\n";
    return 0;
}