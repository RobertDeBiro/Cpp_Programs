/*
 * Smart pointer class
 *
 *  - good:
 *      - no memory leak - pointer deleted
 *  - bad:
 *      - copy constructor can try to delete memory twice - 'SIGTRAP abort' exception
 *      - that is because there is no custom copy constructor but rather default one is used
 *        (shallow copy constructor)
 */

#include <iostream>

//********** Smart pointer class (class holding a pointer) **********
//  - a composition class that is designed to manage dynamically allocated memory and to
//    ensure that memory gets deleted when the smart pointer object goes out of scope
template <typename T>
class Auto_ptr1
{
	T* m_ptr;

public:
	// Pass in a pointer to "own" via the constructor
	Auto_ptr1(T* ptr = nullptr) : m_ptr(ptr)
	{
	}

	// The destructor will make sure it gets deallocated
	~Auto_ptr1()
	{
		delete m_ptr;
	}

	// Overload dereference and 'operator->' so we can use 'Auto_ptr1' like 'm_ptr'
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

void someFunction()
{
	// The 'Resource' in angled braces doesn't need a '*' symbol, since that's supplied by the template
    Auto_ptr1<Resource> ptr(new Resource()); // Note the allocation of memory here ...

    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if (x == 0)
        return; // the function returns early

    // do stuff with ptr here
    ptr->sayHi();

	// ... but no explicit delete needed
}

int main()
{
    std::cout << "*****************************************************\n";

    someFunction();

    std::cout << "*****************************************************\n";
    return 0;
}