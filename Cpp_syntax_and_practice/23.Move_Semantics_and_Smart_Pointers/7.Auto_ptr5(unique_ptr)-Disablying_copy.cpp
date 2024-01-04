/*
 * 'Auto_ptr5' class is the same as 'Auto_ptr4', except it disables copy of object and enables only move
 *  - with this kind of class we cannot initialize one 'Auto_ptr5<Resource>' object with some other,
 *    or we cannot assign one one 'Auto_ptr5<Resource>' object to other
 *  - this class presents 'std::unique_ptr' - only one object can have particular address allocated
 *  - if we want that several objects can have the same address we would use 'std::shared_ptr'
 */

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

	// Copy constructor
	// - disable possibility to copy by using 'delete'
	Auto_ptr5(const Auto_ptr5& source) = delete;

	// Move constructor
	// - transfer ownership of 'a.m_ptr' to 'm_ptr'
	Auto_ptr5(Auto_ptr5&& source) noexcept : m_ptr(source.m_ptr)
	{
		source.m_ptr = nullptr;
	}

	// Copy assignment
	// - disable possibility to copy by using 'delete'
	Auto_ptr5& operator=(const Auto_ptr5& source) = delete;

	// Move assignment
	// - transfer ownership of 'a.m_ptr' to 'm_ptr'
	Auto_ptr5& operator=(Auto_ptr5&& source) noexcept
	{
		// Self-assignment detection
		if (&source == this)
			return *this;

		// Release any resource we're holding
		delete m_ptr;

		// Transfer ownership of 'a.m_ptr' to 'm_ptr'
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
    void sayHi() { std::cout << "Hi!\n"; }
};

Auto_ptr5<Resource> generateResource()
{
	Auto_ptr5<Resource> res(new Resource);
	return res;
} 

int main()
{
    std::cout << "*****************************************************\n";

	Auto_ptr5<Resource> mainres;
	mainres = generateResource();

    std::cout << "*****************************************************\n";
	return 0;
}