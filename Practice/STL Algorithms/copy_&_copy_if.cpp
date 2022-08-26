#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> src{ 1, 5, 2, 4, 3};
    std::cout << "Source vector: ";
    for(const auto elem : src)
        std::cout << elem << " ";
    std::cout << '\n';

    // ******************************* std::copy *******************************
    /*
     * std::copy(InputIt first, InputIt last, OutputIt d_first) -> OutputIt
     *  - copies elements from source container - from [first, last) - to destination container
     *  - returns the iterator to the element in the destination container, one past the last element copied
     *  - it is necessary that std::copy knows the size of destination container
     *     - std::copy() does nothing to expand the destination container
     */
    std::vector<int> dest1(src.size());
    std::copy(src.begin(), src.end(), dest1.begin());
    std::cout << "Dest1 vector: ";
    for(const auto elem : dest1)
        std::cout << elem << " ";
    std::cout << '\n';

    // In following example, std::copy doesn't know the size of the vector,
    // but since std::back_inserter is used it can handle the copy
    std::vector<int> dest2;
    std::copy(src.begin(), src.end(), std::back_inserter(dest2));
    std::cout << "Dest2 vector, using std::back_inserter: ";
    for(const auto elem : dest2)
        std::cout << elem << " ";
    std::cout << '\n';

    // Invalid solution:
    //  - even though vector can dynamically change its size, when using std::copy vector needs to have known size
    // std::vector<int> destINV;
    // std::copy(src.begin(), src.end(), destINV.begin();


    // ******************************* std::copy_if *******************************
    /*
     * std::copy_if(InputIt first, InputIt last, OutputIt d_first, callable_object) -> OutputIt
     *  - copies elements from source container - from [first, last) - to destination container, but only
     *    elements for which callable object returns "true"
     */
    std::vector<int> dest3;
    std::copy_if(src.begin(), src.end(), std::back_inserter(dest3), [](int elem){ return elem > 3; });
    std::cout << "Dest3 elements, using std::copy_if ";
    for(const auto elem : dest3)
        std::cout << elem << " ";
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}