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
    for(int i = 0; i < n; i += 2)
    {
        v.push_back(i);
    }

    int q = 5;

    vector<int>::iterator it_elem, lower;
    for(int i = 0; i < q; i++)
    {
        elem = i * 3;
        it_elem = find(v.begin(), v.end(), elem);
        if(it_elem != v.end())
        {
            std::cout << "Element is found in index: " << std::distance(v.begin(), it_elem) << '\n';
        }
        else
        {
            lower = lower_bound(v.begin(), v.end(), elem);
            std::cout << "Element is not found! lower = " << *lower << "; lower bound index = "
                      << std::distance(v.begin(), lower) << '\n';
        }
    }

    std::cout << "Time taken: " << t.elapsed() << " seconds\n";
    // Time elapsed in average: 0.002937 s

    cout << "*****************************************************\n";
    return 0;
}
