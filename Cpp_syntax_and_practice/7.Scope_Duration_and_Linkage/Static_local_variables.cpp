/*
 * LearnCpp
 * Object_Scope_and_Conversions
 * Summary and quiz
 */

#include <iostream>

bool passOrFail()
{
	//********** Static local variable initialization **********
	// - initialization of static local variable is only done once
	// - only in first passOrFail() call following line will be executed,
	//   in every following will be skipped
    static int s_counter{0};

    return (++s_counter < 4);
}

int main()
{
    std::cout << "*****************************************************\n";

	std::cout << "User #1: " << (passOrFail() ? "Pass\n" : "Fail\n");
	std::cout << "User #2: " << (passOrFail() ? "Pass\n" : "Fail\n");
	std::cout << "User #3: " << (passOrFail() ? "Pass\n" : "Fail\n");
	std::cout << "User #4: " << (passOrFail() ? "Pass\n" : "Fail\n");
	std::cout << "User #5: " << (passOrFail() ? "Pass\n" : "Fail\n");

    std::cout << "*****************************************************\n";
	return 0;
}
