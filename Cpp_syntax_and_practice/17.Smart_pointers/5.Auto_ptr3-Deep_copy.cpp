// Auto_ptr3 class tries to enhance Auto_ptr2 class (std::auto_ptr) by avoiding move semantics
// (because move semantic as implemented in std::auto_ptr can lead to erroneous behavior, because
// it is not real move semantic, but rather some workaround, so it can be unclear to developer
// that pointer is moved to other variable, as stated in LearnCpp page)
//  - Auto_ptr3 tries to enhance that by avoiding move semantics and using deep copy
//  - the problem with this kind of implementation is that more processor resources are used

#include <iostream>

template<typename T>
class Auto_ptr3
{
	T* m_ptr;
public:
	Auto_ptr3(T* ptr = nullptr) : m_ptr(ptr)
	{
	}

	~Auto_ptr3()
	{
		delete m_ptr; // 3b./5b./6b. Calling Resource destructor
	}

	// A copy constructor that implements deep copy
    // - here pointer is not coppied, but rather new address is assigned and pointer content is coppied
	// - const to l-value references prolong the lifetime of r-value, but value cannot be changed
	Auto_ptr3(const Auto_ptr3& source)
	{
		m_ptr = new T; // 2b. Resource (T) is created, calling constructor!
		*m_ptr = *source.m_ptr;
	}

	// A copy assignment that implements deep copy
	Auto_ptr3& operator=(const Auto_ptr3& source)
	{
		// self-assignment guard
		if (&source == this)
			return *this;

		delete m_ptr;

		m_ptr = new T; // 4b. Resource (T) is created, calling constructor!
		*m_ptr = *source.m_ptr;
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

Auto_ptr3<Resource> generateResource()
{
	Auto_ptr3<Resource> res{new Resource}; // 1a. Resource is created, calling Resource constructor
	                                       // 1b. res is initialized, calling Auto_ptr3 constructor
	return res; // 2a. Temporary Auto_ptr3 object is initialized when returning res, calling Auto_ptr3 copy constructor
} // 3a. res is deleted, calling Auto_ptr3 destructor

int main()
{
	Auto_ptr3<Resource> mainres; // 0. Calling Auto_ptr3 constructor
	mainres = generateResource(); // 4a. Calling Auto_ptr3 assignment operator
								  // 5a. Temporary Auto_ptr3 object is deleted, calling Auto_ptr3 destructor

	return 0;
} // 6a. mainres is deleted, calling Auto_ptr3 destructor

// My compiler elides steps 2. and 3.
// - compiler figures that res is ultimately added to mainres, so it doesn't uses temporary object but
//   rather initializes mainres directly with res and then after main() deletes both mainres and res