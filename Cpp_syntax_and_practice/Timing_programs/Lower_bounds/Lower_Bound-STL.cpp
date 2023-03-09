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

    int n = 8;
    int elem;
    vector<int> v;
    for(int i = 0; i < n; i++)
    {
        v.push_back(i);
    }

    int q = 4;

    vector<int>::iterator it_elem, lower;
    for(int i = 0; i < q; i++)
    {
        elem = i * 3;
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

    std::cout << "Time taken: " << t.elapsed() << " seconds\n";
    // Time elapsed in average: 0.00177 s

    cout << "*****************************************************\n";
    return 0;
}
