/*
 * LearnCpp
 * Basic Object-oriented Programming
 * Summary and quiz
 */

#include <iostream>
#include <cmath> // std::sqrt

class Point2d
{
    double m_x;
    double m_y;

public:
    Point2d(double x = 0.0, double y = 0.0) : m_x{ x }, m_y{ y } {}

    void print()
    {
        std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
    }

    friend double distanceFrom(const Point2d &firstPoint, const Point2d &secondPoint);
};

//* Friend function
//  - friend function doesn't have approach to pointer '*this', hence
//    we need to send to it 'Point2d' attributes
double distanceFrom(const Point2d &firstPoint, const Point2d &secondPoint)
{
    return std::sqrt((firstPoint.m_x - secondPoint.m_x)*(firstPoint.m_x - secondPoint.m_x)
                   + (firstPoint.m_y - secondPoint.m_y)*(firstPoint.m_y - secondPoint.m_y));
}

int main()
{
    std::cout << "*****************************************************\n";

    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    first.print();
    second.print();

    std::cout << "Distance between two points: " << distanceFrom(first, second) << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
