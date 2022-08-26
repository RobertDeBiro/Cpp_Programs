/*
 * CTR52-CPP. Guarantee that library functions do not overflow
 *  - link: https://wiki.sei.cmu.edu/confluence/display/cplusplus/CTR52-CPP.+Guarantee+that+library+functions+do+not+overflow
 */

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

void non_compl_copy_example(const std::vector<int>& src);
void compl_copy_example(const std::vector<int>& src);
void non_compl_fill_example(const std::vector<int>& src);
void compl_fill_example(const std::vector<int>& src);

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> src{ 1, 2, 3 };

    //non_compl_copy_example(src);
    compl_copy_example(src);
    //non_compl_fill_example(src);
    compl_fill_example(src);

    std::cout << "*****************************************************\n";
    return 0;
}

void non_compl_copy_example(const std::vector<int>& src)
{
    // it is necessary that std::copy knows the size of destination container
    //  - std::copy() does nothing to expand the destination container
    //  - buffer overflow happens
    std::vector<int> dest;
    std::copy(src.begin(), src.end(), dest.begin());
}

void compl_copy_example(const std::vector<int>& src)
{
    // 1) Sufficient Initial Capacity
    std::vector<int> dest1(src.size());
    std::copy(src.begin(), src.end(), dest1.begin());
    std::cout << "Dest vector (Sufficient Initial Capacity): ";
    printVector(dest1);
    
    // 2) Per-Element Growth
    std::vector<int> dest2;
    std::copy(src.begin(), src.end(), std::back_inserter(dest2));
    std::cout << "Dest vector (Per-Element Growth): ";
    printVector(dest2);

    // 3) Assignment
    std::vector<int> dest3(src);
    std::cout << "Dest vector (Assignment): ";
    printVector(dest3);

    std::cout << "------------------------------\n";
}

void non_compl_fill_example(const std::vector<int>& src)
{
    // it is necessary that std::fill knows the size of destination container
    //  - buffer overflow happens
    std::vector<int> dest;
    std::fill_n(dest.begin(), 10, 0x42); 
}

void compl_fill_example(const std::vector<int>& src)
{
    // 1) Sufficient Initial Capacity
    std::vector<int> dest1(10);  // this is somewhat similiar to next example since here we are fill initializing vector with zeros
    std::fill_n(dest1.begin(), 10, 0x42);
    std::cout << "Dest vector (Sufficient Initial Capacity): ";
    printVector(dest1);

    // 2) Fill Initialization
    std::vector<int> dest2(10, 0x42);
    std::cout << "Dest vector (Fill Initialization): ";
    printVector(dest2);

    std::cout << "------------------------------\n";
}