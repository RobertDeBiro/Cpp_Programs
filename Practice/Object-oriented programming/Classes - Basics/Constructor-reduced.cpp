// Constructors

#include <iostream>
#include <string>

class Ball
{
private:
	std::string m_color{};
	double m_radius{};

public:
    // Following constructor replaces 1., 2. and 4. constructor from non-reduced example
	Ball(const std::string &color = "black", double radius = 10.0)
	{
		m_color = color;
		m_radius = radius;
	}

    // Since, when instantianting object and calling constructor we cannot skip left elements
    // and call right one, we need to create every constructor for right elements
    Ball(double radius)
	{
		m_color = "black";
		m_radius = radius;
	}

	void print()
	{
		std::cout << "color: " << m_color << ", radius: " << m_radius << '\n';
	}
};

int main()
{
	Ball def{};
	def.print();

	Ball blue{ "blue" };
	blue.print();

	Ball twenty{ 20.0 };
	twenty.print();

	Ball blueTwenty{ "blue", 20.0 };
	blueTwenty.print();

	return 0;
}
