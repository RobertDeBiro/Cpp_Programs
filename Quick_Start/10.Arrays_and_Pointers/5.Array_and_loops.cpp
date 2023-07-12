//* Arrays in loops
/**
 *  - loops are typically used with arrays to do one of three things:
 *      1. Calculate a value (e.g. average value, total value)
 *      2. Search for a value (e.g. highest value, lowest value)
 *      3. Reorganize the array (e.g. ascending order, descending order)
 **/
#include <iostream>
#include <iterator> // std::size

int main()
{
    std::cout << "*****************************************************\n";

    const int scores[]{ 84, 92, 76, 81, 56 };
    int scores_size{ static_cast<int>(std::size(scores)) }; // std::size returns unsigned int

    //* Calculate average score
    int sum;
    for (int student{ 0 }; student < scores_size; ++student)
    {
        sum += scores[student];
    }
    double average = static_cast<double>(sum) / scores_size;
    std::cout << "Average score = " << average << '\n';

    /////////////////////////////////////////////////////////////////////////

    //* Search for a highest score
    
    int maxIndex{ 0 }; // Assume the element at index 0 is the largest
    for (int student{ 1 }; student < scores_size; ++student)
    {
        if (scores[student] > scores[maxIndex])
        {
            maxIndex = student;
        }
    }
    std::cout << "The best score was " << scores[maxIndex] << '\n';

    return 0;
}
