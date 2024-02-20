#include <iostream>
#include <thread>

using namespace std;

class Base
{
public:
    void run(int x)
    {
        while (x > 0)
        {
            cout << x << ' ';
            x--;
        }
        cout << '\n';
    }
};

int main()
{
    std::cout << "*****************************************************\n";

    // When using "non-static member function", we need to send function by address, since the funciton
    // is part of the class
    //  - in addition we need also to send an object for which the function is called
    Base b;
    thread t(&Base::run, &b, 10);
    t.join();

    std::cout << "*****************************************************\n";
    return 0;
}