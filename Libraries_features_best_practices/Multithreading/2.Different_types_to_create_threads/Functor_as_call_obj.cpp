#include <iostream>
#include <thread>

using namespace std;

class Base
{
public:
    void operator() (int x)
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

    thread t((Base()), 10);
    t.join();

    std::cout << "*****************************************************\n";
    return 0;
}