#include <iostream>
#include <thread>

using namespace std;

class Base
{
public:
    static void run(int x)
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

    // When using static member function we don't need to instantiate an object and send it to
    // thread() function
    thread t(&Base::run, 10);
    t.join();

    std::cout << "*****************************************************\n";
    return 0;
}