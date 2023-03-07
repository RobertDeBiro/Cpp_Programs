// LearnCpp
// Operator overloading
// Overloading unary operators +, -, and !

#include <iostream>

class Point
{
private:
    double m_x {};
    double m_y {};
    double m_z {};

public:
    Point(double x=0.0, double y=0.0, double z=0.0):
        m_x{x}, m_y{y}, m_z{z}
    {
    }

    // Return a Point
    Point operator+ () const;

    // Convert a Point into its negative equivalent
    Point operator- () const;

    // Return true if the point is set at the origin
    bool operator! () const;

    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }
};

// Convert a Point into its negative equivalent
Point Point::operator+ () const
{
    // Additional solution:
    // return *this
    return { m_x, m_y, m_z };
}

// Convert a Point into its negative equivalent
Point Point::operator- () const
{
    return { -m_x, -m_y, -m_z };
}

// Return true if the point is set at the origin, false otherwise
bool Point::operator! () const
{
    return (m_x == 0.0 && m_y == 0.0 && m_z == 0.0);
}

int main()
{
    std::cout << "*****************************************************\n";

    Point point{}; // use default constructor to set to (0.0, 0.0, 0.0)

    if (!point)
        std::cout << "point is set at the origin.\n";
    else
        std::cout << "point is not set at the origin.\n";
    
    point = {1, 2, 3};

    if (!point)
        std::cout << "point is set at the origin.\n";
    else
        std::cout << "point is not set at the origin.\n";
    
    std::cout << "------------------------------------\n";

    Point point_minus{ -point };
    std::cout << "Unary (-) point:\n";
    std::cout << "m_x = " << point_minus.getX() << '\n';
    std::cout << "m_x = " << point_minus.getY() << '\n';
    std::cout << "m_x = " << point_minus.getZ() << '\n';

    std::cout << "------------------------------------\n";

    Point point_plus{ +point_minus };
    std::cout << "Unary (+) point:\n";
    std::cout << "m_x = " << point_plus.getX() << '\n';
    std::cout << "m_x = " << point_plus.getY() << '\n';
    std::cout << "m_x = " << point_plus.getZ() << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}