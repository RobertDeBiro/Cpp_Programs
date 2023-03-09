/*
 * Sample Input:
 * 8
 * 1 1 2 2 6 9 9 15
 * 4
 * 1
 * 4
 * 9
 * 15
 * 
 * HackerRank:
 *  - https://www.hackerrank.com/challenges/cpp-lower-bound/problem?isFullScreen=true
 */

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
        lower = lower_bound(v.begin(), v.end(), elem);
        if(elem == *lower)
        {
            std::cout << "Yes " << std::distance(v.begin(), lower) + 1 << '\n';
        }
        else
        {
            std::cout << "No " << std::distance(v.begin(), lower) + 1 << '\n';
        }
    }

    cout << "*****************************************************\n";
    return 0;
}
