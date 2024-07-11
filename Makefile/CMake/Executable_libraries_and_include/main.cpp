#include <iostream>
#include "Point3d.hpp" // Can be included because it is included in Point target as a PUBLIC
#include "Vector3d.hpp"

int main()
{
	Point3d p{ 1.0, 2.0, 3.0 };
	Vector3d v{ 2.0, 2.0, -3.0 };

	p.print();
	p.moveByVector(v);
	p.print();

	p.moveByMacro(RANDOM_MACRO_VAL);
	p.print();
	v.print();

	return 0;
}
