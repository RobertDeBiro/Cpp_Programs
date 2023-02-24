// LearnCpp
// Operator overloading
// Overloading the I/O operators

#include <iostream>
#include <limits> // std::numeric_limits
#include <numeric> // std::gcd

class Fraction
{
private:
	int m_numerator{};
	int m_denominator{};

public:
	Fraction(int numerator=0, int denominator=1):
		m_numerator{numerator}, m_denominator{denominator}
	{
		// We put reduce() in the constructor to ensure any new fractions we make get reduced!
		// Any fractions that are overwritten will need to be re-reduced
		reduce();
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
	friend Fraction operator*(const Fraction& f1, int value);
	friend Fraction operator*(int value, const Fraction& f1);
	friend std::istream& operator>>(std::istream& in, Fraction& f);
	friend std::ostream& operator<<(std::ostream& out, const Fraction& f);

	void print() const
	{
		std::cout << m_numerator << '/' << m_denominator << '\n';
	}
};

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
	return Fraction(f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator);
}

Fraction operator*(const Fraction& f1, int value)
{
	return Fraction(f1.m_numerator * value, f1.m_denominator);
}

Fraction operator*(int value, const Fraction& f1)
{
	return Fraction(f1.m_numerator * value, f1.m_denominator);
}

std::istream& operator>>(std::istream& in, Fraction& f)
{
    in >> f.m_numerator;

    // Ignore the '/' separator
	in.ignore(std::numeric_limits<std::streamsize>::max(), '/');

    in >> f.m_denominator;

    f.reduce();

    return in;
}

std::ostream& operator<<(std::ostream& out, const Fraction& f)
{
    out << f.m_numerator << '/' << f.m_denominator;
    return out;
}

int main()
{
    std::cout << "*****************************************************\n";

	Fraction f1;
	std::cout << "Enter fraction 1: ";
	std::cin >> f1;

	Fraction f2;
	std::cout << "Enter fraction 2: ";
	std::cin >> f2;

	std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n';

    std::cout << "*****************************************************\n";
	return 0;
}
