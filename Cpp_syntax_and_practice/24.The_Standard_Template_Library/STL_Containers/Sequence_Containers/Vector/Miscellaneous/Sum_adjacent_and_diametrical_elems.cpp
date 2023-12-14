/*
 * C++ Primer
 * Exercise Section 3.3.3
 *  - Exercise 3.20
 * 
 * In this example I left on purpose some error prone implementation
 *  - counters 'i' and 'j' in our 'for' loops are 'unsigned integers', means that they cannot be negative
 *    - 'decltype(v.size())' returns type of 'v.size()' which is 'size_type' which is
 *      'long long unsigned int'
 *  - the problem is in variable 'j' that is decreasing each interation, hence there is a possibility
 *    that the code will try to decrease it below '0'
 *  - that really happens when the vector contains only '1' element - 'for' loop goes to infinity and
 *    we get SIGSEGV signal (segmentation fault)
 *  - therefore it is the best that our counters are 'signed integers', especially if they are decreasing
 *    each iteration
 */

#include <iostream>
#include <vector>

int main()
{
    std::cout << "*****************************************************\n";

    std::cout << "Type number of integers you want to read: ";
    int n;
    std::cin >> n;

    std::cout << "Insert those integers: ";
    int elem;
    std::vector<int> v;
    for(int i = 0; i < n; i++)
    {
        std::cin >> elem;
        v.push_back(elem);
    }

    std::cout << "--------------------------------------------\n";

    std::cout << "Sum and print adjacent elements:\n";
    int sum1 = 0;
    decltype(v.size()) i;
    for(i = 0; i < v.size() - 1; i++)
    {
        sum1 = v[i] + v[i + 1];
        std::cout << i + 1 << ". adjacent pair sum = " << sum1 << '\n';
    }

    std::cout << "--------------------------------------------\n";

    std::cout << "Sum and print diametric elements:\n";
    int sum2 = 0;
    decltype(v.size()) j;
    for(i = 0, j = v.size() - 1; i <= j; i++, j--)
    {
        if(i == j)
            sum2 = v[i];
        else
            sum2 = v[i] + v[j];
        std::cout << i + 1 << ". diametric pair sum = " << sum2 << '\n';
    }

    std::cout << "*****************************************************\n";
    return 0;
}