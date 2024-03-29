/*
 * LearnCpp
 * Basic Object-oriented Programming
 * Non-static member initialization
 */

#include <iostream>

class Ball
{
private:
	std::string m_color{ "black" };
	double m_radius{ 10.0 };

public:
	// Default constructor with no parameters
	Ball() = default;

	// Constructor with only radius parameter (color will use default value)
	Ball(double radius) : m_radius{ radius } {}

	// Constructor with only color parameter (radius will use default value)
    Ball(const std::string& color) : m_color { color } {}

	// Constructor with both color and radius parameters
	Ball(const std::string &color, double radius) : m_color{ color }, m_radius{ radius } {}

	void print()
	{
		std::cout << "color: " << m_color << "\tradius: " << m_radius << '\n';
	}
};

int main()
{
    std::cout << "*****************************************************\n";

	Ball def;
	def.print();

	Ball blue{ "blue" };
	blue.print();

	Ball twenty{ 20.0 };
	twenty.print();

	Ball blueTwenty{ "blue", 20.0 };
	blueTwenty.print();

    std::cout << "*****************************************************\n";
	return 0;
}
