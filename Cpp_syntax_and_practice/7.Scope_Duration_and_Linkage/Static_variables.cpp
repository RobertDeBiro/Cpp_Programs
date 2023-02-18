// Summary and quiz

#include <iostream>

bool passOrFail()
{
    static int counter{0};

    return (++counter < 4);
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
