/*
 * LearnCpp
 * Arrays, Strings, and Dynamic Allocation
 * Arrays and loops
 */

#include <iostream>
#include <iterator> // std::size (but, can be used without <iterator>)

int main()
{
    std::cout << "*****************************************************\n";

    constexpr int scores[]{ 84, 92, 76, 81, 56 };
    int scores_size{ static_cast<int>(std::size(scores)) }; // std::size returns unsigned int

    int maxIndex{ 0 }; // Assume the element at index 0 is the largest

    // Look for an index of the highest score in the rest of the array
    for (int student{ 1 }; student < scores_size; ++student)
    {
        if (scores[student] > scores[maxIndex])
        {
            maxIndex = student;
        }
    }

    std::cout << "The best score was " << scores[maxIndex] << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
