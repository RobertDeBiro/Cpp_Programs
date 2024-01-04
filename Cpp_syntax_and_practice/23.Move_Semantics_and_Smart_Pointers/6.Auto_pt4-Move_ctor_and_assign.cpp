/*
 * 'Auto_ptr4' class enhances:
 *  - 'Auto_ptr2' class ('std::auto_ptr') by using move constructor and move assignment operator
 *     rather than move semantics 
 *  - 'Auto_ptr3' class by moving content and not copying it
 * 
 * Comparison to deep copy example:
 *  - instead of copying our 'Resource' twice (once for the copy constructor and once for
 *    the copy assignment), we transfer it twice
 */

#include <iostream>

template <typename T>
class Auto_ptr4
{
    T* m_ptr;
public:
    Auto_ptr4(T* ptr = nullptr) : m_ptr{ ptr }
    {
    }

    ~Auto_ptr4()
    {
        delete m_ptr;
    }

    // A copy constructor that implements deep copy
    // - here just for comparison with move constructor, it is never called
    Auto_ptr4(const Auto_ptr4& source)
    {
        m_ptr = new T;
        *m_ptr = *source.m_ptr;
    }

    // Move constructor
    // - res is not coppied to temporary object (to the source variable), but rather moved, which is QUICKER
    // - r-value references prolong the lifetime of r-value and the value can be changed
    Auto_ptr4(Auto_ptr4&& source) noexcept : m_ptr(source.m_ptr)
    {
        source.m_ptr = nullptr;
    }

    // Copy assignment with deep copy
    // - here just for comparison with move assignment, it is never called
    Auto_ptr4& operator=(const Auto_ptr4& source)
    {
        if(&source == this)
            return *this;

        delete m_ptr;
        m_ptr = new T;
        *m_ptr = *source.m_ptr;

        return *this;
    }

    // Move assignment
    // - 'res' is moved to temporary object (to the source variable)
    Auto_ptr4& operator=(Auto_ptr4&& source) noexcept
    {
        if(&source == this)
            return *this;

        delete m_ptr;
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

Auto_ptr4<Resource> generateResource()
{
	Auto_ptr4<Resource> res(new Resource); // 1.a 'Resource' is created, calling 'Resource' constructor
                                           // 1.b 'res' is initialized, calling 'Auto_ptr4' constructor
	return res; // 2. Temporary object is initialized when returning 'res', calling move constructor
                //     - the C++ specification has a special rule that says: Automatic objects returned
                //       from a function by value can be moved even if they are l-values
} 

int main()
{
    std::cout << "*****************************************************\n";

	Auto_ptr4<Resource> mainres; // 0. Calling 'Auto_ptr3' constructor
	mainres = generateResource(); // 3. Temporary object is moved to 'mainres', calling move assignment

    std::cout << "*****************************************************\n";
	return 0;
} // 4. 'mainres' is deleted, calling destructor
