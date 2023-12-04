/*
 * LearnCpp
 * Basic Object-oriented Programming
 * Constructor member initializer list
 */

#include <iostream>
#include <cstdint>

class RGBA
{
public:
    using colorType = std::uint_fast8_t;

private:
    colorType m_red{};
    colorType m_green{};
    colorType m_blue{};
    colorType m_alpha{};

public:
    //* Initializer list with default values
    RGBA(colorType red = 0, colorType green = 0, colorType blue = 0, colorType alpha = 255)
        : m_red{ red }, m_green{ green }, m_blue{ blue }, m_alpha{ alpha }
    {
    }

    void print()
    {
        // 'std::uint_fast8_t' needs to be casted to int because 'std::cout'
        // would otherwise print it as character
        std::cout << "r=" << static_cast<int>(m_red)
                  << " g=" << static_cast<int>(m_green)
                  << " b=" << static_cast<int>(m_blue)
                  << " a=" << static_cast<int>(m_alpha) << '\n';
    }
};

int main()
{
    std::cout << "*****************************************************\n";

	RGBA teal{ 0, 127, 127 };
	teal.print();

    std::cout << "*****************************************************\n";
	return 0;
}
