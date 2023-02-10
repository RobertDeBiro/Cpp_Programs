// LearnCpp
// Inheritance
// Constructors and initialization of derived classes

#include <string>
#include <iostream>

class Fruit
{
    std::string m_name{};
    std::string m_color{};

public:
    Fruit(std::string name, std::string color)
        : m_name{ name }, m_color{ color }
    {
    }

	const std::string& getName() const { return m_name; }
	const std::string& getColor() const { return m_color; }
};

class Apple : public Fruit
{
    double m_fiber{};

public:
    Apple(std::string name, std::string color, double fiber)
        : Fruit{name, color}, m_fiber{ fiber }
    {
    }

    double getFiber() const { return m_fiber; }
};

class Banana : public Fruit
{
public:
    Banana(std::string name, std::string color)
        : Fruit{name, color}
    {
    }
};

std::ostream& operator<< (std::ostream& out, const Apple& a)
{
    out << "Apple(" << a.getName() << ", " << a.getColor() << ", " << a.getFiber() << ')';
    return out;
}

std::ostream& operator<< (std::ostream& out, const Banana& b)
{
    out << "Banana(" << b.getName() << ", " << b.getColor() << ')';
    return out;
}

int main()
{
    std::cout << "*****************************************************\n";

	const Apple a{ "Red delicious", "red", 4.2 };
	std::cout << a << '\n';

	const Banana b{ "Cavendish", "yellow" };
	std::cout << b << '\n';

    std::cout << "*****************************************************\n";
	return 0;
}
