#include <iostream>

template <typename T>
class Auto_ptr1
{
    T* m_ptr;
public:
    Auto_ptr1(T* ptr = nullptr) : m_ptr(ptr)
    {
    }

/*
    Classes by default uses copy constructor that implements shallow copy (provided by the compiler)
        - shallow copy means that pointer is coppied to other pointer
    
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
};

int main()
{
    Auto_ptr1<Resource> res1{ new Resource() };

    // Since compiler will by default use shallow copy in copy ctor
    // the same memory address will be both in res1 and res2 which
    // will cause same memory deleted twice and ultimately SIGTRAP abort
    Auto_ptr1<Resource> res2(res1);

	return 0;
}
