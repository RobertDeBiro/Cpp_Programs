#include <iostream>
#include <vector>

class ContClass
{
    int m_x{};
    int m_y{};

public:
    ContClass() { std::cout << "Default constructor called!\n"; }
    ContClass(int x, int y) : m_x{ x }, m_y{ y }
    {
        std::cout << "Constructor called!\n";
    }
};

int main()
{
    std::cout << "*****************************************************\n";

    ContClass contClass1; // Default constuctor called
    std::vector<ContClass> vecDef1; // No constuctor called
    std::vector<ContClass> vecDef2 { {1, 2} }; // Constuctor called

    std::cout << "*****************************************************\n";
    return 0;
}