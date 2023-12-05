/*
 * bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
 * 
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/equal
 */

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";
    std::cout << std::boolalpha;

    std::vector<int> varVect1{ 1, 2, 3, 4, 5 };
    std::vector<int> varVect2{ 1, 2, 3, 4, 5 };
    std::vector<int> varVect3{ 0, 2, 3, 4, 6 };

    bool eq1{ std::equal(varVect1.begin(), varVect1.end(), varVect2.begin()) };
    bool eq2{ std::equal(varVect1.begin(), varVect1.end(), varVect3.begin()) };
    bool eq3a{ std::equal((varVect1.begin()+1), (varVect1.begin()+3), (varVect3.begin()+1)) };
    bool eq3b{ std::equal((varVect1.begin()+1), (varVect1.begin()+3), (varVect3.begin()+2)) };

    std::cout << "Vectors are equal: " << eq1 << '\n';
    std::cout << "Vectors are equal: " << eq2 << '\n';
    std::cout << "Vectors are equal: " << eq3a << '\n';
    std::cout << "Vectors are equal: " << eq3b << '\n';
    
    std::cout << std::noboolalpha;
    std::cout << "*****************************************************\n";
    return 0;
}