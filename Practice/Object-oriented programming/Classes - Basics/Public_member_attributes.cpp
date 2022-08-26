#include <iostream>

class IntPair
{
public:
	int m_first{};
	int m_second{};

	void print()
	{
	    std::cout << "Pair(" << m_first << ", " << m_second << ")\n";
	}
};

int main()
{
	IntPair p{ 2, 2 }; // We can set public member variables from main function
	p.print();

	return 0;
}
