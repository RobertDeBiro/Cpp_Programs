/*
 * 'emplace' takes the arguments necessary to construct an object in place,
 * whereas 'insert' takes (a reference to) an object.
 *  - emplace construct objects inside of the vector
 *  - insert copies objects into the vector
 */

#include <iostream>
#include <vector>

struct Foo
{
    int m_n;
    double m_x;

    Foo(int n, double x) : m_n(n), m_x(x)
    {
        std::cout << "Constructed\n";
        std::cout << "m_n = " << m_n << '\n';
        std::cout << "m_x = " << m_x << '\n';
    }
};

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<Foo> varVect;
    varVect.reserve(5);

    std::cout << "Emplace: ";
    varVect.emplace(varVect.end(), 42, 3.1416);

    std::cout << "Insert: ";
    // 'Foo(42, 3.1416)' calls constructor
    varVect.insert(varVect.end(), Foo(42, 3.1416));

    // We must insert an object because 'insert()' won't constructor vector in place
    //! varVect.insert(varVect.end(), 42, 3.1416);

    std::cout << "*****************************************************\n";
    return 0;
}