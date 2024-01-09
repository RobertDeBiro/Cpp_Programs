#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

int main() {
    cout << "*****************************************************\n";

    int n;
    cin >> n;

    vector<int> v;
    int elem;
    for(int i = 0; i < n; i++)
    {
        cin >> elem;
        v.push_back(elem);
    }

    int q;
    cin >> q;

    vector<int>::iterator it_elem, lower;
    for(int i = 0; i < q; i++)
    {
        cin >> elem;
        it_elem = find(v.begin(), v.end(), elem);
        if(it_elem != v.end())
        {
            std::cout << "Yes " << std::distance(v.begin(), it_elem) + 1 << '\n';
        }
        else
        {
            lower = lower_bound(v.begin(), v.end(), elem);
            if (lower == v.end())
                std::cout << "No " << std::distance(v.begin(), lower) << '\n';
            else
                std::cout << "No " << std::distance(v.begin(), lower) + 1 << '\n';

        }
    }

    cout << "*****************************************************\n";
    return 0;
}
