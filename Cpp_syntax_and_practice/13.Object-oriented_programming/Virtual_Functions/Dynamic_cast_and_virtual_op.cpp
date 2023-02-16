// LearnCpp
// Virtual Functions
// Summary and quiz

#include <iostream>
#include <vector>

class Point
{
private:
	int m_x{};
	int m_y{};
	int m_z{};

public:
	Point(int x, int y, int z)
		: m_x{ x }, m_y{ y }, m_z{ z }
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const Point& p)
	{
		return out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ')';
	}
};

class Shape
{
public:
    virtual std::ostream& print(std::ostream& out) const = 0;

    // operator<< cannot be virtualized, so we are using it not to print the result (which is usually done)
    // but rather we are calling a function which will print the resul
    friend std::ostream& operator<<(std::ostream& out, const Shape& s)
    {
        return s.print(out);
    }

    virtual ~Shape() = default;
};

class Triangle : public Shape
{
    Point m_p1;
    Point m_p2;
    Point m_p3;

public:
    Triangle(const Point& p1, const Point& p2, const Point& p3)
        : m_p1{ p1 }, m_p2{ p2 }, m_p3{ p3 }
    {
    }

    virtual std::ostream& print(std::ostream& out) const
    {
        out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ")";
        return out;
    }
};

class Circle : public Shape
{
    Point m_p1;
    int m_rad{};

public:
    Circle(const Point& p1, int rad)
        : m_p1{ p1 }, m_rad{ rad }
    {
    }

    virtual std::ostream& print(std::ostream& out) const
    {
        out << "Circle(" << m_p1 << ", radius " << m_rad << ")";
        return out;
    }

    int getRadius() const { return m_rad; }
};

int getLargestRadius(const std::vector<Shape*>& v)
{
	int largestRadius{ 0 };

	// Loop through all the shapes in the vector
	for (const auto element : v)
	{
		// Ensure the dynamic cast succeeds by checking for a null pointer result
		if (auto c{ dynamic_cast<const Circle*>(element) })
		{
			largestRadius = std::max(largestRadius, c->getRadius());
		}
	}
	return largestRadius;
}

int main()
{
    std::cout << "*****************************************************\n";

	std::vector<Shape*> v{
	    new Circle{Point{1, 2, 3}, 7},
	    new Triangle{Point{1, 2, 3}, Point{4, 5, 6}, Point{7, 8, 9}},
	    new Circle{Point{4, 5, 6}, 3}
	};

	// type deduction (auto) does not drop pointers
	for (const auto elem : v)
        std::cout << *elem << '\n';

	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

    // delete each element in the vector here

    std::cout << "*****************************************************\n";
	return 0;
}
