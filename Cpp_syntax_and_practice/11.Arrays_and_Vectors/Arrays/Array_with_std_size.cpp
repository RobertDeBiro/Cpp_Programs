// LearnCpp - Arrays and loops

#include <iostream>
#include <iterator> // for std::size - this is not mandatory, it works without inclusion of iterator

int main()
{
    constexpr int scores[]{ 84, 92, 76, 81, 56 };

    int maxIndex{ 0 }; // Assume the element at index 0 is the largest

    // now look for an index of the highest score in the rest of the array
    for (int student{ 1 }; student < static_cast<int>(std::size(scores)); ++student) // std::size returns unsigned int
    {
        if (scores[student] > scores[maxIndex])
        {
            maxIndex = student;
        }
    }

    std::cout << "The best score was " << scores[maxIndex] << '\n';

    return 0;
}
