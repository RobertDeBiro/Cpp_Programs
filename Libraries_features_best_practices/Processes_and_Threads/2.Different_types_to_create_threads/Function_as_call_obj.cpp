#include <iostream>
#include <thread>

using namespace std;

void fun_call_obj(int x)
{
    // First x is evaluated, i.e. checked if it is bigger than 0, and then is decremented
    while (x-- > 0)
    {
        cout << x << ' ';
    }
    cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    thread t(fun_call_obj, 10);
    t.join();

    std::cout << "*****************************************************\n";
    return 0;
}