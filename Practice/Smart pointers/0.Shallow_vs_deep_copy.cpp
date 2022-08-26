#include <iostream>
#include <cstring> // strlen()
#include <cassert> // assert()

class MyString
{
private:
    char* m_data{};
    int m_length{};

public:
    MyString(const char* source = "" )
    {
        assert(source); // make sure source isn't a null string

        // Find the length of the string
        // Plus one character for a terminator
        m_length = std::strlen(source) + 1;

        // Allocate a buffer equal to this length
        m_data = new char[m_length];

        // Copy the parameter string into our internal buffer
        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source[i];
    }

    /*
    Copy constructor implementing shallow copy (provided by the compiler)
     - it coppies pointer to other pointer
    MyString::MyString(const MyString& source)
        : m_length { source.m_length }
        , m_data { source.m_data }
    {
    }
    */

    // Copy constructor implementing deep copy
    //  - it assigns new memory address and coppies content of pointer to other pointer
    MyString(const MyString& source)
    {
        // first we need to deallocate any value that this string is holding!
        delete[] m_data;

        // because m_length is not a pointer, we can shallow copy it
        m_length = source.m_length;

        // m_data is a pointer, so we need to deep copy it if it is non-null
        if (source.m_data)
        {
            // allocate memory for our copy
            m_data = new char[m_length];

            // do the copy
            for (int i{ 0 }; i < m_length; ++i)
                m_data[i] = source.m_data[i];
        }
        else
            m_data = nullptr;
    }

    ~MyString() // destructor
    {
        // We need to deallocate our string
        delete[] m_data;
    }

    char* getString() { return m_data; }
    int getLength() { return m_length; }
};

int main()
{
    // We want to dynamically allocate resource for our string.
    // There are other options to assign "Hello world" to a variable:
    //  1) char hello[] { "Hello, world!" }
    //  2) const char* hello{ "Hello, world!" }
    //  3) std::string hello{ "Hello, world!" }
    //      - the best idea because it is a class that dynamically manages memory, just like MyString that we created
    
    MyString hello{ "Hello, world!" };
    {
        MyString copy{ hello }; // use copy constructor
    } // copy is a local variable, so it gets destroyed here.
      // When using default copy constructor with shallow copy, the destructor deletes copy's string, which leaves hello with a dangling pointer

    std::cout << hello.getString() << '\n'; // When using shallow copy, this will have undefined behavior

    return 0;
}