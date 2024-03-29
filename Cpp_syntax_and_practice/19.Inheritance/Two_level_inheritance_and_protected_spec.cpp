/*
 * LearnCpp
 * Inheritance
 * Summary and quiz
 */

#include <iostream>
#include <string>

class Fruit
{
    std::string m_name{};
    std::string m_color{};

public:
    Fruit(const std::string& name, const std::string& color)
        : m_name{ name }, m_color{ color }
    {
    }

    const std::string& getName() const { return m_name; }
    const std::string& getColor() const { return m_color; }
};

class Apple: public Fruit
{
// The previous constructor we used for Apple had a fixed name ("apple").
// We need a new constructor for "GrannySmith" to use to set the name of the fruit
protected:
	Apple(const std::string& name, const std::string& color)
		: Fruit{ name, color }
	{
	}

public:
	Apple(const std::string& color="red")
		: Fruit{ "apple", color }
	{
	}
};

class GrannySmith : public Apple
{
public:
    // Accessing 'Apple' constructor inside 'protected' access specifier
    GrannySmith() : Apple{ "granny smith apple", "green" }
    {
    }
};

class Banana : public Fruit
{
public:
    Banana() : Fruit{ "banana", "yellow" }
    {
    }
};

int main()
{
    std::cout << "*****************************************************\n";

	Apple a{ "red" };
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    std::cout << "*****************************************************\n";
	return 0;
}
