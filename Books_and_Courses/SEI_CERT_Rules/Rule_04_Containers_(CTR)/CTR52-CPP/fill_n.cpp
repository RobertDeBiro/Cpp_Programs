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
     *  - it is necessary that std::fill_n knows the size of destination container
     *      - std::fill_n does nothing to expand the destination container
     */
    // std::vector<int> dest;
    // std::fill_n(dest.begin(), 10, 0x42);

    /*
     * Compliant
     *  - initialize vector with wanted amount of elements
     */
    std::vector<int> dest1(10); 
    std::fill_n(dest1.begin(), 10, 0x42);
    std::cout << "Dest vector (Initialize with 0 and then fill):\n";
    printVector(dest1);

    std::cout << "-----------------------\n";

    std::vector<int> dest2(10, 0x42);
    std::cout << "Dest vector (Initialize with wanted value):\n";
    printVector(dest2);

    std::cout << "*****************************************************\n";
    return 0;
}
