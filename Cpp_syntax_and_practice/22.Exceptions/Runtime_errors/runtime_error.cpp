#include <iostream>
#include <stdexcept> // std::runtime_error

class Fraction
{
private:
    int m_numerator{};
    int m_denominator{};

public:
    //* Throwing exception from user-defined constructor
    Fraction(int numerator, int denominator)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
        if(m_denominator == 0)
            throw std::runtime_error("ERROR: Invalid denominator");
    }

    friend std::ostream& operator<<(std::ostream &out, const Fraction &frac);
};

std::ostream& operator<<(std::ostream &out, const Fraction &frac)
{
    out << frac.m_numerator << "/" << frac.m_denominator;
    return out;
}

int main()
{
    std::cout << "*****************************************************\n";

    std::cout << "Enter the numerator: ";
    int num{};
    std::cin >> num;

    std::cout << "Enter the denominator: ";
    int denom{};
    std::cin >> denom;

    try
    {
        Fraction frac{num, denom};
        std::cout << "Your fraction is: " << frac << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "*****************************************************\n";
    return 0;
}
