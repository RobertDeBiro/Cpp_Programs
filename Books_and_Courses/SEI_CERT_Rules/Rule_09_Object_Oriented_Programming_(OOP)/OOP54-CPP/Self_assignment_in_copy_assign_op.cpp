#include <iostream>
#include <exception>

class Resource
{
public:
    int m_x;
    Resource(int x) : m_x{ x } { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

class TestClass
{
public:
    Resource* m_ptr;

    // Constructor
    TestClass(Resource* ptr = nullptr) : m_ptr{ ptr } {}

    // Destructor
    ~TestClass() { delete m_ptr; }

    // Copy constructor
    TestClass(const TestClass& source)
    {
        try
        {
            m_ptr = new Resource(*source.m_ptr);
            // The same as:
            // m_ptr = new Resource();
            // *m_ptr = *source.m_ptr;
        }
        catch (std::bad_alloc&) // catch std::bad_alloc, but don't save it into any object
        {
            m_ptr = nullptr;
            throw;
        }
    }

    // Move constructor
    TestClass(TestClass&& source) noexcept : m_ptr(source.m_ptr)
    {
        source.m_ptr = nullptr;
    }

    // Copy assignment
    TestClass& operator=(const TestClass& source)
    {
        // For non-compliant solution comment following 2 lines
        if(&source == this)
            return *this;

        delete m_ptr;
        try
        {
            m_ptr = new Resource(*source.m_ptr);
        }
        catch (std::bad_alloc&)
        {
            m_ptr = nullptr;
            throw;
        }

        return *this;
    }

    // Move assignment
    TestClass& operator=(TestClass&& source) noexcept
    {
        // For non-compliant solution comment following 2 lines
        if(&source == this)
            return *this;

        delete m_ptr;
        m_ptr = source.m_ptr;
        source.m_ptr = nullptr;
        return *this;
    }
};

int main()
{
    std::cout << "*****************************************************\n";

    TestClass test(new Resource(2));
    // Self-copy assignment
    test = test;
    // In compliant scenario 2 will be printed, whereas in non-compliant
    // some garbage (e.g. -11630005939)
    std::cout << test.m_ptr->m_x << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}