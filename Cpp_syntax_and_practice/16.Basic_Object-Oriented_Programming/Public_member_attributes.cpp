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
    std::cout << "*****************************************************\n";

	//********** Initialize public member variables from main() **********
	IntPair p{ 2, 2 };
	p.print();

    std::cout << "*****************************************************\n";
	return 0;
}
