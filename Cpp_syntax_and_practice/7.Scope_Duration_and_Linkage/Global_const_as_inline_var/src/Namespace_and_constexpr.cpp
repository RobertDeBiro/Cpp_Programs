/*
 * LearnCpp
 * Object_Scope_and_Conversions
 * Summary and quiz
 */

#include <iostream>
#include "../inc/Constants.hpp"

int main()
{
    std::cout << "*****************************************************\n";

	std::cout << "How many students are in your class? ";
	int students{};
	std::cin >> students;


	if (students > constants::max_class_size)
		std::cout << "There are too many students in this class!\n";
	else
		std::cout << "This class isn't too large.\n";

    std::cout << "*****************************************************\n";
	return 0;
}
