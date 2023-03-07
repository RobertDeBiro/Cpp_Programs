#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
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

    sort(v.begin(), v.end());

    for(const auto& elem : v)
        cout << elem << ' ';
    cout << '\n';

    cout << "*****************************************************\n";
    return 0;
}
