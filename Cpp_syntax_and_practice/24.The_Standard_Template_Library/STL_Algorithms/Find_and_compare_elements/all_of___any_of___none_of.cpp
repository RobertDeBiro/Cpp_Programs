/*
 * std::all_of( InputIt first, InputIt last, UnaryPredicate p ) -> bool
 *
 * std::any_of( InputIt first, InputIt last, UnaryPredicate p ) -> bool
 * 
 * std::none_of( InputIt first, InputIt last, UnaryPredicate p ) -> bool
 * 
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/all_any_none_of
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main()
{
    std::cout << "*****************************************************\n";
    std::cout << std::boolalpha;

    std::vector<int> varVect1{ 2, 4, 6 };
    std::vector<int> varVect2{ 2, 4, 5 };
    std::vector<int> varVect3{ 1, 3, 5 };

    auto is_even{
        [](const int elem)
        {
            return (elem % 2 == 0); 
        }
    };

    bool allEven1{ std::all_of(varVect1.begin(), varVect1.end(), is_even)};
    std::cout << std::setw(50) << std::left << "varVect1 contains all even elements: "
                               << std::right << allEven1 << '\n';

    bool atLeastOneEven1{ std::any_of(varVect1.begin(), varVect1.end(), is_even)};
    std::cout << std::setw(50) << std::left << "varVect1 contains at least one even elements: "
                               << std::right << atLeastOneEven1 << '\n';

    bool noneEven1{ std::none_of(varVect1.begin(), varVect1.end(), is_even)};
    std::cout << std::setw(50) << std::left << "varVect1 doesn't contain any even element: "
                               << std::right << noneEven1 << '\n';

    std::cout << "------------------------------------------------------------\n";

    bool allEven2{ std::all_of(varVect2.begin(), varVect2.end(), is_even)};
    std::cout << std::setw(50) << std::left << "varVect2 contains all even elements: "
                               << std::right << allEven2 << '\n';

    bool atLeastOneEven2{ std::any_of(varVect2.begin(), varVect2.end(), is_even)};
    std::cout << std::setw(50) << std::left << "varVect2 contains at least one even elements: "
                               << std::right << atLeastOneEven2 << '\n';

    bool noneEven2{ std::none_of(varVect2.begin(), varVect2.end(), is_even)};
    std::cout << std::setw(50) << std::left << "varVect2 doesn't contain any even element: "
                               << std::right << noneEven2 << '\n';

    std::cout << "------------------------------------------------------------\n";

    bool allEven3{ std::all_of(varVect3.begin(), varVect3.end(), is_even)};
    std::cout << std::setw(50) << std::left << "varVect3 contains all even elements: "
                               << std::right << allEven3 << '\n';

    bool atLeastOneEven3{ std::any_of(varVect3.begin(), varVect3.end(), is_even)};
    std::cout << std::setw(50) << std::left << "varVect3 contains at least one even elements: "
                               << std::right << atLeastOneEven3 << '\n';

    bool noneEven3{ std::none_of(varVect3.begin(), varVect3.end(), is_even)};
    std::cout << std::setw(50) << std::left << "varVect3 doesn't contain any even element: "
                               << std::right << noneEven3 << '\n';

    std::cout << "------------------------------------------------------------\n";

    std::cout << std::noboolalpha;
    std::cout << "*****************************************************\n";
    return 0;
}