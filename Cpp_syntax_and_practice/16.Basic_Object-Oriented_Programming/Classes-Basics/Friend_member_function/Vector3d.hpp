#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include "Point3d.hpp" // Point3d class definition included

class Vector3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Vector3d(double x = 0.0, double y = 0.0, double z = 0.0)
		: m_x{ x }, m_y{ y }, m_z{ z }
	{
	}

	void print() const;

	// If we want to use friend function from other class, that class needs to be defined first - 
	// therefore, Point3d.h was included at the beginning of the file
	//  - moveByVector needs to be friend function in order to access Vector3d private members
	friend void Point3d::moveByVector(const Vector3d& v);
};

#endif