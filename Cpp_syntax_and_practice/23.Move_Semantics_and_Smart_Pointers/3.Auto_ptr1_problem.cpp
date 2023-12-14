#include <iostream>

template <typename T>
class Auto_ptr1
{
    T* m_ptr;

public:
    Auto_ptr1(T* ptr = nullptr) : m_ptr(ptr)
    {
    }

    //********** Default copy constructor provided by compiler **********
    // Default copy constructor provided by compiler implements shallow copy
    // - pointer is coppied into another variable, eventually having two variables
    //   containing the same address: 'm_ptr' and 'source.m_ptr'
/*
    Auto_ptr1(const Auto_ptr1& source)
        : m_ptr { source.m_ptr }
    {
    }
*/

    ~Auto_ptr1()
    {
        delete m_ptr;
    }

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void sayHi() { std::cout << "Hi!\n"; }
};

int main()
{
    std::cout << "*****************************************************\n";

    Auto_ptr1<Resource> res1{ new Resource() };

    // Since compiler will by default use shallow copy in copy constructor
    // the same memory address will be both in 'res1' and 'res2' which
    // will cause same memory deleted twice and ultimately 'SIGTRAP abort' exception
    Auto_ptr1<Resource> res2(res1);

    std::cout << "*****************************************************\n";
	return 0;
}
