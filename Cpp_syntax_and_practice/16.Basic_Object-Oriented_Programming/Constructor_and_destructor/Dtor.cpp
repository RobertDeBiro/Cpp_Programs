/*
 * LearnCpp
 * Basic Object-oriented Programming
 * Summary and quiz
 */

#include <iostream>

class HelloWorld
{
private:
	char* m_data{};

public:
	HelloWorld()
	{
        std::cout << "Creating dynamically allocated m_data!\n";
		m_data = new char[14];

		const char* init{ "Hello, World!" };
		for (int i = 0; i < 14; ++i)
			m_data[i] = init[i];
	}

	~HelloWorld()
	{
        std::cout << "Deleting dynamically allocated m_data!\n";
		delete[] m_data;
	}

	void print() const
	{
		std::cout << m_data << '\n';
	}

};

int main()
{
    std::cout << "*****************************************************\n";

	HelloWorld hello{};
	hello.print();

    std::cout << "*****************************************************\n";
    return 0;
}
