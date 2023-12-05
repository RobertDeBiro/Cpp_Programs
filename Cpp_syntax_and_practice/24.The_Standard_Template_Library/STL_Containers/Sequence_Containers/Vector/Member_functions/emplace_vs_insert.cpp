/*
 * Emplace takes the arguments necessary to construct an object in place,
 * whereas insert takes (a reference to) an object.
 *  - emplace construct objects inside of the vector
 *  - insert copies objects into the vector
 * 
 * References:
 *  - https://stackoverflow.com/questions/14788261/c-stdvector-emplace-vs-insert#:~:text=Emplace%20takes%20the%20arguments%20necessary,a%20reference%20to)%20an%20object.
 *  - https://stackoverflow.com/questions/4303513/push-back-vs-emplace-back
 */

#include <iostream>
#include <vector>

struct Foo
{
    int m_n;
    double m_x;

    Foo(int n, double x) : m_n(n), m_x(x) { std::cout << "Constructed\n"; }
};

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<Foo> varVect;
    varVect.reserve(5);

    std::cout << "Emplace: ";
    varVect.emplace(varVect.end(), 42, 3.1416);

    std::cout << "Insert: ";
    varVect.insert(varVect.end(), Foo(42, 3.1416));
    // ERROR: We must insert an object
    //varVect.insert(varVect.end(), 42, 3.1416);

    std::cout << "*****************************************************\n";
    return 0;
}