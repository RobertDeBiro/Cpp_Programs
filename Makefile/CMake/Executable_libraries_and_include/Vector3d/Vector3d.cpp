#include <iostream>
#include "Vector3d.hpp"

#ifdef RANDOM_MACRO
void Vector3d::print() const
{
	std::cout << "Vector(" << m_x << " , " << m_y << " , " << m_z << ")\n";
}
#endif
