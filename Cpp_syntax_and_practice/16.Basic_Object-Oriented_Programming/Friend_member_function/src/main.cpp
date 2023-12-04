#include <iostream>
#include "../inc/Point3d.hpp"
#include "../inc/Vector3d.hpp"

int main()
{
    std::cout << "*****************************************************\n";

	Point3d p{ 1.0, 2.0, 3.0 };
	Vector3d v{ 2.0, 2.0, -3.0 };

	p.print();
	p.moveByVector(v);
	p.print();

    std::cout << "*****************************************************\n";
	return 0;
}
