/*
 * 'Auto_ptr3' class tries to enhance 'Auto_ptr2' class ('std::auto_ptr') by avoiding move semantics
 *  - it does that by using deep copy
 * 
 *  - good:
 *      - no memory leak - pointer deleted
 *      - program won't try to delete the same memory twice
 *      - code designer aware of current object status
 *  - bad:
 *      - more allocating/deallocating memories happens
 *         - deep copy always allocate new memory i.e. always allocates new resource
 *      - possibly a lot of content needs to be coppied
 */

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

	//********** Deep copy **********
	//* A copy constructor that implements deep copy
    // - here pointer is not coppied, but rather new address is assigned and pointer content is coppied
	// - const to l-value references prolong the lifetime of r-value, but value cannot be changed
	Auto_ptr3(const Auto_ptr3& source)
	{
		m_ptr = new T; // 2b. 'Resource' (T) is created, calling constructor!
		*m_ptr = *source.m_ptr;
	}

	//* A copy assignment that implements deep copy
	Auto_ptr3& operator=(const Auto_ptr3& source)
	{
		// self-assignment guard
		if (&source == this)
			return *this;

		// Inside copy constructor we don't need to delete 'm_ptr' because 'm_ptr' is already empty
		delete m_ptr;

		m_ptr = new T; // 4b. Resource (T) is created, calling constructor!
		*m_ptr = *source.m_ptr;
		return *this; // returned because of chaining
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

Auto_ptr3<Resource> generateResource()
{
	Auto_ptr3<Resource> res{new Resource}; // 1a. 'Resource' is created, calling 'Resource' constructor
	                                       // 1b. 'res' is initialized, calling 'Auto_ptr3' constructor
	return res; // 2a. Temporary 'Auto_ptr3' object is initialized when returning 'res', calling 'Auto_ptr3' copy constructor
} // 3a. res is deleted, calling Auto_ptr3 destructor

int main()
{
    std::cout << "*****************************************************\n";

	Auto_ptr3<Resource> mainres;  // 0. Calling 'Auto_ptr3' constructor
	mainres = generateResource(); // 4a. Calling 'Auto_ptr3' assignment operator
								  // 5a. Temporary Auto_ptr3 object is deleted, calling Auto_ptr3 destructor

    std::cout << "*****************************************************\n";
	return 0;
} // 6a. mainres is deleted, calling Auto_ptr3 destructor

// My compiler elides steps 2. and 3.
// - compiler figures that res is ultimately added to mainres, so it doesn't uses temporary object but
//   rather initializes mainres directly with res and then after main() deletes both mainres and res