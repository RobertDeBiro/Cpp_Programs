#include <iostream>
#include "../inc/Point3d.hpp"
#include "../inc/Vector3d.hpp" // Vector3d class definition included

void Point3d::print() const
{
	std::cout << "Point(" << m_x << " , " << m_y << " , " << m_z << ")\n";
}

// If we want to define function that uses Vector3d class,
// we need to fully see Vector3d class definition
void Point3d::moveByVector(const Vector3d& v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;
}