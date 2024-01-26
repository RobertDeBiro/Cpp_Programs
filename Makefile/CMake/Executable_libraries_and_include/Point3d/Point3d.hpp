#ifndef POINT3D_HPP
#define POINT3D_HPP

class Vector3d; // 'Vector3d' class declaration

class Point3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Point3d(double x = 0.0, double y = 0.0, double z = 0.0)
		: m_x{ x }, m_y{ y }, m_z{ z }
	{

	}

	void print() const;

	// If we want to declare function that uses 'Vector3d' class,
	// we need to at least see 'Vector3d' declaration
	void moveByVector(const Vector3d& v);

	void moveByMacro(int macro);
};

#endif