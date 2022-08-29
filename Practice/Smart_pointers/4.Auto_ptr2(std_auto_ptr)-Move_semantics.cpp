#include <iostream>

// Implementing the class Auto_ptr2, similar to Auto_ptr1, but that doesn't uses default copy
// constructor with shallow copy, but rather custom copy constructor and assignment operator that
// implements MOVE SEMANTICS
//
// This class represents implementation of the first smart pointer used in C++, called std::auto_ptr
//  - its usage removed in C++17 due to several flaws
//  - replacement for this smart pointer class is std::unique_ptr
template <typename T>
class Auto_ptr2
{
    T* m_ptr;
public:
    Auto_ptr2(T* ptr = nullptr) : m_ptr(ptr)
    {
    }

    ~Auto_ptr2()
    {
        delete m_ptr;
    }

    // A copy constructor that implements move semantics
    // - in this example we again copy pointer to another pointer, hence doing shallow copy,
    //   but ultimately source pointer is deleted, so memory won't be deleted twice and
    //   SIGTRAP abort error won't appear
    Auto_ptr2(Auto_ptr2& source) // note: not const
    {
        m_ptr = source.m_ptr; // transfer our dumb pointer from the source to our local object
        source.m_ptr = nullptr; // make sure the source no longer owns the pointer
    }

    // An assignment operator that implements move semantics
    Auto_ptr2& operator=(Auto_ptr2& source) // note: not const
    {
        // self-assignment guard
        if(&source == this) 
            return *this;

        delete m_ptr; // make sure we deallocate any pointer the destination is already holding first
        m_ptr = source.m_ptr; // then transfer our dumb pointer from the source to the local object
        source.m_ptr = nullptr; // make sure the source no longer owns the pointer
        return *this; // return the existing object so we can chain this operator
    }

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr;  }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
	Auto_ptr2<Resource> res1(new Resource());
	Auto_ptr2<Resource> res2; // Start as nullptr

	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

	res2 = res1; // res2 assumes ownership, res1 is set to null

	std::cout << "Ownership transferred\n";

	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

	return 0;
}
