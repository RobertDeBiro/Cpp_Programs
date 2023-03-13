#include <vector>
#include <iostream>
#include <set>
#include <iterator>
using namespace std;

template <typename T>
void printSet(T varSet)
{
    for(auto elem : varSet)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main() {
    std::cout << "*****************************************************\n";

    int q;
    cin >> q;

    set<int> s;
    set<int>::const_iterator s_it;
    int y;
    int x;
    for(int i = 0; i < q; i++)
    {
        cin >> y >> x;
        if(y == 1)
        {
            s.insert(x);
        }
        else if (y == 2)
        {
            s_it = s.find(x);
            if(s_it != s.end())
                s.erase(s_it);
        }
        else
        {
            s_it = s.find(x);
            if(s_it != s.end())
                cout << "Yes\n";
            else
                cout << "No\n";
        }
    }

    std::cout << "Set: ";
    printSet(s);

    std::cout << "*****************************************************\n";
    return 0;
}