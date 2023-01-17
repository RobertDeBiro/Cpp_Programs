// Auto_ptr5 class is the same as Auto_ptr4, except it disables copy of object and enables only move
//  - with this kind of class we cannot initialize one Auto_ptr5<Resource> object with some other
//    (as shown in 3.Auto_ptr1_problem.cpp example), or we cannot assign one one Auto_ptr5<Resource> object
//    to other (as shown in 4.Auto_ptr2(std_auto_ptr)-Move_semantics)
//  - therefore, this class presents std::unique_ptr - only one object can have particular address allocated
//  - if we want that several objects can have the same address we would use std::shared_ptr

#include <iostream>

template<typename T>
class Auto_ptr5
{
	T* m_ptr;
public:
	Auto_ptr5(T* ptr = nullptr)
		:m_ptr(ptr)
	{
	}

	~Auto_ptr5()
	{
		delete m_ptr;
	}

	// Copy constructor -- no copying allowed!
	Auto_ptr5(const Auto_ptr5& source) = delete;

	// Move constructor
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr5(Auto_ptr5&& source) noexcept
		: m_ptr(source.m_ptr)
	{
		source.m_ptr = nullptr;
	}

	// Copy assignment -- no copying allowed!
	Auto_ptr5& operator=(const Auto_ptr5& source) = delete;

	// Move assignment
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr5& operator=(Auto_ptr5&& source) noexcept
	{
		// Self-assignment detection
		if (&source == this)
			return *this;

		// Release any resource we're holding
		delete m_ptr;

		// Transfer ownership of a.m_ptr to m_ptr
		m_ptr = source.m_ptr;
		source.m_ptr = nullptr;

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_ptr5<Resource> generateResource()
{
	Auto_ptr5<Resource> res(new Resource);
	return res;
} 

int main()
{
	Auto_ptr5<Resource> mainres;
	mainres = generateResource();

	return 0;
}