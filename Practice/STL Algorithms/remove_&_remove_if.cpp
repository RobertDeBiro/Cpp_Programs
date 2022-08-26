#include <iostream>
#include <vector>
#include <algorithm>

void printv(const std::vector<int>& v)
{
    for (const auto elem : v)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> v;
    for(int i = 0; i <= 2; i++) {
        for (int i = 0; i < 5; i++)
            v.push_back(i);
    }
    std::cout << "Initial vector:\n";
    printv(v);

    // ******************************* std::remove *******************************
    /*
     * std::remove_if(ForwardIt first, ForwardIt last, const T& value) -> ForwardIt
     *  - removes all elements that have values equal to the one specified
     *  - elements are not removed but rather placed at the end of the container
     *  - removed elements are 2, 2, 2, whereas elements placed at the end are 2, 3, 4
     *     - elements placed at the end have unspecified values!
     */
    auto endv0 = std::remove(v.begin(), v.end(), 2);
    std::cout << "Vector size after removing = " << v.size() << '\n';
    std::cout << "Vector after removing elements with value 2:\n";
    printv(v);
    std::cout << "Return from std::remove_if is: " << *endv0 << '\n';

    // ******************************* std::remove_if *******************************
    /*
     * std::remove_if(ForwardIt first, ForwardIt last, callable object) -> ForwardIt
     *  - removes all elements for which callable object returns true
     */
    auto endv = std::remove_if(begin(v), end(v), [](int elem) { return (elem == 1); });
    std::cout << "Vector size after removing = " << v.size() << '\n';
    std::cout << "Vector after removing elements with value 3:\n";
    printv(v);
    std::cout << "Return from std::remove_if is: " << *endv << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}