#include <iostream>
#include <string>

// It is enough to set keyword 'virtual' only once, for the most base class
// for which we want to virtualize the function
//  - every function that overrides the virtual function from the base class
//    will be virtualized
class A
{
public:
    virtual std::string getName() const { return "A"; }
};

class B: public A
{
public:
    std::string getName() const { return "B"; }
};

class C: public B
{
public:
    std::string getName() const { return "C"; }
};

class D: public C
{
public:
    std::string getName() const { return "D"; }
};

int main()
{
    std::cout << "*****************************************************\n";

    C c;
    A& rBase1{ c };
    std::cout << "rBase1 is a " << rBase1.getName() << '\n';

    // Showing that 'getName()' from class 'B' will be also virtualized
    // even though the function is not stated as 'virtual'
    D d;
    B& rBase2{ d };
    std::cout << "rBase2 is a " << rBase2.getName() << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}