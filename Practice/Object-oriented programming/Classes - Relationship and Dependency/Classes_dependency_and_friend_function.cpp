// Friend functions and classes

#include <iostream>

class Vector3d; // Vector3d class declaration

class Point3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Point3d(double x = 0.0, double y = 0.0, double z = 0.0)
		: m_x{x}, m_y{y}, m_z{z}
	{
	}

	void print() const
	{
		std::cout << "Point(" << m_x << " , " << m_y << " , " << m_z << ")\n";
	}

    // If we want to DECLARE function that uses Vector3d class,
	// we need to at least see Vector3d declaration
	void moveByVector(const Vector3d& v);
};

class Vector3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Vector3d(double x = 0.0, double y = 0.0, double z = 0.0)
		: m_x{x}, m_y{y}, m_z{z}
	{
	}

	void print() const
	{
		std::cout << "Vector(" << m_x << " , " << m_y << " , " << m_z << ")\n";
	}

	// If we want to use function from other class, that class needs to be defined first
    //  - moveByVector needs to be friend function in order to access Vector3d private members
	friend void Point3d::moveByVector(const Vector3d& v);
};

// If we want to define function that uses Vector3d class,
// we need to fully see Vector3d class definition
void Point3d::moveByVector(const Vector3d& v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
}

int main()
{
	Point3d p{1.0, 2.0, 3.0};
	Vector3d v{2.0, 2.0, -3.0};

	p.print();
	p.moveByVector(v);
	p.print();

	return 0;
}
