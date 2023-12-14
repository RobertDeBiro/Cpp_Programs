#include <iostream>
#include <set>

// User-defined data type
class A
{
public:
    int m_x;
    A(int x = 0) : m_x{x} { std::cout << "Construct A object\n"; }

    // This "copy constructor" is not mandatory, 'insert()' function use the default one
    //  - we created it to print the information, but since we created it, 'insert()' won't
    //    use default one anymore, so in addition we need to also copy a value
    A(const A& rhs)
    {
        m_x = rhs.m_x;
        std::cout << "Copy constructed A object into A object declared in set\n";
    }

    bool operator < (const A& rhs) const { return m_x < rhs.m_x; }
};

int main()
{
    std::cout << "*****************************************************\n";

    //* set.insert()
    //  - insert() needs to receive already constructed object
    std::cout << "Using set.insert(): \n";
    std::set<A> setInsert;
    A a(10);
    setInsert.insert(a);
    for (const auto& elem : setInsert)
        std::cout << "setInsert elements: " << elem.m_x << '\n';

    std::cout << "---------------------------------------\n";

    //* set.emplace()
    //  - emplace can receive value for variable needed for constructing an object
    //  - emplace constructs an object in place, i.e. it constructs it inside the set object
    std::cout << "Using set.emplace(): \n";
    std::set<A> setEmplace;
    setEmplace.emplace(10);
    for (const auto& elem : setEmplace)
        std::cout << "setEmplace elements: " << elem.m_x << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
