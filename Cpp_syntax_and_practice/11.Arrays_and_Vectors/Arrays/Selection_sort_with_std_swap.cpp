// LearnCpp
// Arrays, Strings, and Dynamic Allocation
// Sorting an array using selection sort

#include <iostream>
#include <utility> // std::swap

int main()
{
	std::cout << "*****************************************************\n";
	
	constexpr int length{ 5 };
	int array[length]{ 30, 50, 20, 10, 40 };

	// Step through each element of the array
	// (except the last one, which will already be sorted by the time we get there)
	for (int startIndex{ 0 }; startIndex < length - 1; ++startIndex)
	{
		// biggestIndex is the index of the biggest element we have encountered in this iteration
		// Start by assuming the biggest element is the first element of this iteration
		int biggestIndex{ startIndex };

		// Then look for a bigger element in the rest of the array
		for (int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex)
		{
			// If we've found an element that is bigger than our previously found biggest
			if (array[currentIndex] > array[biggestIndex])
				// then keep track of it
				biggestIndex = currentIndex;
		}

		// biggestIndex is now the biggest element in the remaining array
        // swap our start element with our biggest element (this sorts it into the correct place)
		std::swap(array[startIndex], array[biggestIndex]);
	}

	// Now that the whole array is sorted, print our sorted array as proof it works
	for (int index{ 0 }; index < length; ++index)
		std::cout << array[index] << ' ';

	std::cout << '\n';

	std::cout << "*****************************************************\n";
	return 0;
}
