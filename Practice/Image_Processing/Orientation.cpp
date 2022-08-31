// A C++ program to find orientation of three points
// more info:
//  - https://www.geeksforgeeks.org/orientation-3-ordered-points/

#include <iostream>
using namespace std;

struct Point {
	int x, y;
};

// To find orientation of ordered triplet (p1, p2, p3).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p1, Point p2, Point p3)
{
	int val = (p2.y - p1.y) * (p3.x - p2.x)
			- (p2.x - p1.x) * (p3.y - p2.y);

	if (val == 0)
		return 0; // collinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// Driver program to test above functions
int main()
{
	Point p1 = { 0, 0 }, p2 = { 4, 4 }, p3 = { 1, 2 };
	int o = orientation(p1, p2, p3);
	if (o == 0)
		cout << "Linear";
	else if (o == 1)
		cout << "Clockwise";
	else
		cout << "CounterClockwise";
	cout << endl;

	p1 = { 0, 0 }, p2 = { 4, 4 }, p3 = { 1, 1 };
	o = orientation(p1, p2, p3);
	if (o == 0)
		cout << "Linear";
	else if (o == 1)
		cout << "Clockwise";
	else
		cout << "CounterClockwise";
	cout << endl;

	p1 = { 1, 2 }, p2 = { 4, 4 }, p3 = { 0, 0 };
	o = orientation(p1, p2, p3);
	if (o == 0)
		cout << "Linear";
	else if (o == 1)
		cout << "Clockwise";
	else
		cout << "CounterClockwise";
	cout << endl;

	p1 = { 1, 1 }, p2 = { 4, 4 }, p3 = { 2, 5 };
	o = orientation(p1, p2, p3);
	if (o == 0)
		cout << "Linear";
	else if (o == 1)
		cout << "Clockwise";
	else
		cout << "CounterClockwise";
	
	return 0;
}
