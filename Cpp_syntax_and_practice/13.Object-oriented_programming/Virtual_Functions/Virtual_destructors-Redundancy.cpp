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
        terminate();
    }
};

int main()
{
    Base* b1{ new Base() };
    delete b1;

    std::cout << "--------------------\n";

    Base* b2{ new Derived() };
    delete b2;

    std::cout << "--------------------\n";

    Derived* d{ new Derived() };
    delete d;

    return 0;
}