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

        // Find the length of the string (plus one character for a terminator)
        m_length = std::strlen(source) + 1;

        // Allocate a buffer equal to this length
        m_data = new char[m_length];

        // Copy the parameter string into our internal buffer
        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source[i];
    }

    //********** Shallow copy **********
    // - default copy constructor and default assignment operator are provided by the compiler,
    //   we don't need to create themn
    // - they are implemented by using shallow copy - attribute is directly coppied to corresponding
    //   attribute

    //* Default copy constructor
/*
    MyString(const MyString& source)
        : m_length { source.m_length }
        , m_data { source.m_data }
    {
    }
*/

    //* Default assignment operator
/*
    MyString& operator= (const MyString& source)
    {
        if (this == &source)
            return *this;
        
        m_length = source.m_length;
        m_data = source.m_data;

        return *this;
    }
*/

    //********** Deep copy **********
    // - copy constructor and assignment operator must be implemented by user when implementing deep copy
    // - should be created when one of member variables is pointer
    //   - with deep copy we assign new memory address and copy content of pointer to other pointer

    //* User-defined copy constructor
    MyString(const MyString& source)
    {
        // Because 'm_length' is not a pointer, we can shallow copy it
        m_length = source.m_length;

        // 'm_data' is a pointer, so we need to deep copy it if it is non-null
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

    //* User defined assignment operator
    MyString operator=(const MyString& source)
    {
        if (this == &source)
            return *this;

        // First we need to deallocate any value that this string is holding!
        // - this was not needed with copy constructor because than 'm_data' is for sure empty
        delete[] m_data;

        // Because 'm_length' is not a pointer, we can shallow copy it
        m_length = source.m_length;

        // 'm_data' is a pointer, so we need to deep copy it if it is non-null
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
        
        return *this; // returning in order to support chaining
    }

    ~MyString() // destructor
    {
        // We need to deallocate our string
        // - when using shallow copy in following line we will have an exception because our address
        //   will try to be deleted twice
        delete[] m_data;
    }

    char* getString() { return m_data; }
    int getLength() { return m_length; }
};

int main()
{
    std::cout << "*****************************************************\n";

    // We want to dynamically allocate resource for our string.
    // There are other options to assign "Hello world" to a variable:
    //  1) char hello[] { "Hello, world!" }
    //  2) const char* hello{ "Hello, world!" }
    //  3) std::string hello{ "Hello, world!" }
    //      - the best idea because it is a class that dynamically manages memory,
    //        just like 'MyString' that we created
    
    MyString hello{ "Hello, world!" };
    {
        MyString copy{ hello }; // use copy constructor
    } // copy is a local variable, so it gets destroyed here
      // When using default copy constructor with shallow copy, the destructor deletes copy's string,
      // which leaves hello with a dangling pointer

    std::cout << hello.getString() << '\n'; // When using shallow copy, this will have undefined behavior

    std::cout << "*****************************************************\n";
    return 0;
}