// LearnCpp - Object Scope and Conversions
// Summary and quiz

#include <iostream>
#include "constants.hpp"

int main()
{
	std::cout << "How many students are in your class? ";
	int students{};
	std::cin >> students;


	if (students > constants::max_class_size)
		std::cout << "There are too many students in this class";
	else
		std::cout << "This class isn't too large";

	return 0;
}
