/*
 * Sample input:
 * 6
 * 1 4 6 2 8 9
 * 2
 * 2 4
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    cout << "*****************************************************\n";

    // Insert vector length
    int n;
    cin >> n;

    // Inserts elements in vector
    //  - since we used direct initialization, we can assign vector just like we would do with array,
    //    we don't have to use push_back()
    vector<int> v(n);
    for(int i = 0; i < n; i++)
        cin >> v[i];

    int er_index;
    cin >> er_index;

    v.erase(v.begin() + (er_index - 1));

    int range1, range2;
    cin >> range1 >> range2;
    v.erase(v.begin() + (range1 - 1), v.begin() + (range2 - 1));

    cout << v.size() << '\n';
    for(const auto& elem : v)
        cout << elem << ' ';
    cout << '\n';

    cout << "*****************************************************\n";
    return 0;
}
