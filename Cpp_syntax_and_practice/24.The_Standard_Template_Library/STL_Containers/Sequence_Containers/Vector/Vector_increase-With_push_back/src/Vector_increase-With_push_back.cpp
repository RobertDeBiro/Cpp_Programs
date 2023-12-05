/*
 * Pluralsight
 * 
 * Everytime vector is increased every its element is coppied to a new memory location
 *  - in the printout we will see that, every time new element is added, copy constructor is called
 *    for every of those elements, because everything is coppied to a new location
 */

#include <iostream>
#include <vector>
#include "../inc/Resource.hpp"

using std::vector;
using std::cout;

int main()
{
    std::cout << "*****************************************************\n";

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

    std::cout << "*****************************************************\n";
    return 0;
} // Destructing r

