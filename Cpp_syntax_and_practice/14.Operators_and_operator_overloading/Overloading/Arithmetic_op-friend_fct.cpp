// LearnCpp
// Operator overloading
// Overloading the arithmetic operators using friend functions

#include <iostream>
#include <numeric> // std::gcd

class Fraction
{
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction(int num, int denom=1)
        : m_numerator{ num }, m_denominator{ denom }
    {
        // We put reduce() in the constructor to ensure any new fractions we make get reduced!
		// Any fractions that are overwritten will need to be re-reduced.
        reduce();
    }

    void print()
    {
        std::cout << m_numerator << "/" << m_denominator << '\n';
    }

    void reduce()
    {
        int gcd{ std::gcd(m_numerator, m_denominator) };
        if (gcd)
        {
            m_numerator /= gcd;
            m_denominator /= gcd;
        }
    }

    friend Fraction operator*(const Fraction& f1, const Fraction& f2);
    friend Fraction operator*(const Fraction& f, int v);
    friend Fraction operator*(int v, const Fraction& f);
};

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    return Fraction{f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator};
}

Fraction operator*(const Fraction& f, int v)
{
    return Fraction{f.m_numerator * v, f.m_denominator};
}

Fraction operator*(int v, const Fraction& f)
{
    return Fraction{f.m_numerator * v, f.m_denominator};
}

int main()
{
    std::cout << "*****************************************************\n";

    Fraction f1{2, 5};
    f1.print();

    Fraction f2{3, 8};
    f2.print();

    Fraction f3{ f1 * f2 };
    f3.print();

    Fraction f4{ f1 * 2 };
    f4.print();

    Fraction f5{ 2 * f2 };
    f5.print();

    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print();

    Fraction f7{0, 6};
    f7.print();

    std::cout << "*****************************************************\n";
    return 0;
}
