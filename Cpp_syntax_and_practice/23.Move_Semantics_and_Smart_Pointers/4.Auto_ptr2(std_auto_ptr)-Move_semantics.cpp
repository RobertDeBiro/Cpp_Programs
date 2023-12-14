/*
 * 'Auto_ptr2' class is similar to 'Auto_ptr1', but it doesn't uses default copy constructor with
 * shallow copy
 *   - it uses custom copy constructor and assignment operator that implements MOVE SEMANTICS
 *   - move semantics is actually shallow copy but with additional step in which we assign
 *     pointer object to 'nullptr'
 * 
 * This class represents implementation of the first smart pointer used in C++, called 'std::auto_ptr'
 *  - 'std::auto_ptr' is removed in C++17 due to several flaws
 *  - replacement for this smart pointer class is 'std::unique_ptr'
 * 
 *  - good:
 *      - no memory leak - pointer deleted
 *      - program won't try to delete the same memory twice
 *  - bad:
 *      - code designer may not be aware that object is moved to another object
 *      - pointer is deleted using non-array delete
 */

#include <iostream>

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

    //********** Move semantics **********
    // - in this example we again copy pointer to another pointer, hence doing shallow copy,
    //   but ultimately source pointer is deleted, so program won't try to delete memory twice and
    //   SIGTRAP abort error won't appear
    // - there are two changes comparing to class 'Auto_ptr1'
    //    1. Input parameter 'source' is not 'const' (because it needs to be changed to 'nullptr')
    //    2. 'source.m_ptr' is set to 'nullptr'

    //* Copy constructor that implements move semantics
    Auto_ptr2(Auto_ptr2& source)
    {
        m_ptr = source.m_ptr; // transfer our dumb pointer from the source to our local object
        source.m_ptr = nullptr; // make sure the source no longer owns the pointer
    }

    //* An assignment operator that implements move semantics
    Auto_ptr2& operator=(Auto_ptr2& source)
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
    void sayHi() { std::cout << "Hi!\n"; }
};

int main()
{
    std::cout << "*****************************************************\n";

	Auto_ptr2<Resource> res1(new Resource());
	Auto_ptr2<Resource> res2; // Start as nullptr

	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

	res2 = res1; // res2 assumes ownership, res1 is set to null

    std::cout << "-----------------------------------\n";
	std::cout << "Ownership transferred\n";

	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

    std::cout << "*****************************************************\n";
	return 0;
}
