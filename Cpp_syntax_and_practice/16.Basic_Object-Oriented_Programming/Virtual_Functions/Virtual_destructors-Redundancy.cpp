#include <iostream>

class Base
{
public:
    virtual ~Base()
    {
        terminate();
    }

    void terminate()
    {
        std::cout << "Calling Base destructor!\n";
    }
};

class Derived: public Base
{
public:
    ~Derived()
    {
        std::cout << "Calling Derived destructor!\n";
        // Following part is redundant since destructor of the derived object will always eventually call
        // the destructor of the base object
        terminate();
    }
};

int main()
{
    std::cout << "*****************************************************\n";

    Base* b1{ new Base() };
    delete b1;

    std::cout << "--------------------\n";

    Base* b2{ new Derived() };
    delete b2;

    std::cout << "--------------------\n";

    Derived* d{ new Derived() };
    delete d;

    std::cout << "*****************************************************\n";
    return 0;
}