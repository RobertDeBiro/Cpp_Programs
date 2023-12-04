#include <iostream>

class DefCon
{
    int m_a;

public:
    DefCon()
    {
        std::cout << "Default constructor without default parameter is called!\n";
    }

    DefCon(int a = 0)
    {
        std::cout << "Default constructor with default parameter is called!\n";
    }
};

int main()
{
    // Won't compile due to ambiguity
    //! DefCon a;

    // Compiles, but it doesn't call constructor
    //  - the same would be if we would declare, for example, only integer variable (int a)
    DefCon a();

    return 0;
}
