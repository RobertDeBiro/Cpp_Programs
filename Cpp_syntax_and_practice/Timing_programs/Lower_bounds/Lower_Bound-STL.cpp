#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>
#include "../Timer/Timer.hpp"
using namespace std;

int main() {
    cout << "*****************************************************\n";

    Timer t;

    int n = 14;
    int elem;
    vector<int> v;
    for(int i = 0; i < n; i++)
    {
        v.push_back(i);
    }

    int q = 5;

    vector<int>::iterator it_elem, lower;
    for(int i = 0; i < q; i++)
    {
        elem = i * 3;
        lower = lower_bound(v.begin(), v.end(), elem);
        if(elem == *lower)
        {
            std::cout << "Element is found in index: " << std::distance(v.begin(), lower) << '\n';
        }
        else
        {
            std::cout << "Element is not found! lower = " << *lower << "; lower bound index = "
                      << std::distance(v.begin(), lower) << '\n';
        }
    }

    std::cout << "Time taken: " << t.elapsed() << " seconds\n";
    // Time elapsed in average: 0.002481 s
    // - this program is little bit faster than the same one, but with 'find()' function because here we use
    //   one STL function less

    cout << "*****************************************************\n";
    return 0;
}
