#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

void printVector(const std::vector<int>& varVect)
{
    for(int elem : varVect)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> src{ 1, 2, 3 };

    /*
     * Non-compliant
     *  - segmentation fault happens (buffer overflow)
     *  - it is necessary that std::copy knows the size of destination container
     *      - std::copy does nothing to expand the destination container
     */
    // std::vector<int> dest;
    // std::copy(src.begin(), src.end(), dest.begin());

    /*
     * Compliant
     *  1) Initialize vector with sufficient amount of elements (using source.size())
     *  2) Use std::back_inserter for "per-element growth"
     *  3) Initialize destination vector with source vector
     */
    std::vector<int> dest1(src.size());
    std::copy(src.begin(), src.end(), dest1.begin());
    std::cout << "Dest vector (Sufficient amount of elements):\n";
    printVector(dest1);
    
    std::cout << "-----------------------\n";

    // 2) Per-Element Growth
    std::vector<int> dest2;
    std::copy(src.begin(), src.end(), std::back_inserter(dest2));
    std::cout << "Dest vector (per-Element Growth):\n";
    printVector(dest2);

    std::cout << "-----------------------\n";

    // 3) Assignment
    std::vector<int> dest3(src);
    std::cout << "Dest vector (initialize with source):\n";
    printVector(dest3);

    std::cout << "*****************************************************\n";
    return 0;
}
