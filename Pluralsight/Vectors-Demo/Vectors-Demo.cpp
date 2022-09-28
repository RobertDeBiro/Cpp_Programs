// This example shows that, everytime vector is increased, every its element is coppied
// to a new memory location
// - therefore, in the printour we will see calling copy constructor for every element, every
//   time new element is added, because everything is coppied to a new location

#include <iostream>
#include <vector>
#include "Resource.hpp"

using std::vector;
using std::cout;

int main()
{
    vector numbers{ 0, 1, 2 };
    numbers.push_back(-2);
    numbers[0] = 3;

    for (int i : numbers)
        cout << i << '\n';

    Resource r("local"); // Constructing r

    {
        //braces only for scope
        cout << "-------------------" << '\n';
        vector<Resource> resources;
        resources.push_back(r);
        cout << "-------------------" << '\n';
        resources.push_back(Resource("first"));
        cout << "-------------------" << '\n';
        resources.push_back(Resource("second"));
        cout << "-------------------" << '\n';
    } // Destructing resources

    return 0;
} // Destructing r

