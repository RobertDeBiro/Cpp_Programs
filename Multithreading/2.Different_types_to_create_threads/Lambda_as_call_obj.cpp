#include <iostream>
#include <thread>

using namespace std;

int main()
{
    std::cout << "*****************************************************\n";

    auto lam_call_obj{ [](int x){
        while (x > 0)
        {
            cout << x << ' ';
            x--;
        }
        cout << '\n';
    }};
    thread t(lam_call_obj, 10);
    t.join();

    std::cout << "*****************************************************\n";
    return 0;
}