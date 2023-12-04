/*
 * Using generated default constructor and created default constructor is the same
 *  - created default constructor is mandatory when class contains multiple constructors
 */

#include <iostream>

//* Generated default constructor
//  - no member initialization
class Gdc_nmi
{
    int m_x;
    int m_y;
public:
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

//* Generated default constructor
//  - zero member initialization
class Gdc_zmi
{
    int m_x{};
    int m_y{};
public:
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

//* Generated default constructor
//  - non-static member initialization
class Gdc_mi
{
    int m_x{ 2 };
    int m_y{ 5 };
public:
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

//* Multiple constructors
//  - no member initialization
class Mc_nmi
{
    int m_x;
    int m_y;
public:
    Mc_nmi() = default;

    // When we have some constructor defined, default constructor won't be automatically generated
    Mc_nmi(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

//* Multiple constructors
//  - zero member initialization
class Mc_zmi
{
    int m_x{};
    int m_y{};
public:
    Mc_zmi() = default;
    Mc_zmi(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

//* Multiple constructors
//  - non-static member initialization
class Mc_mi
{
    int m_x{ 2 };
    int m_y{ 5 };
public:
    Mc_mi() = default;
    Mc_mi(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

int main()
{
    std::cout << "*****************************************************\n";

    //********** Objects created via generated default constructor **********
    // Variables not initalized (printing undefined values)
    Gdc_nmi gdc_nmi_1;
    std::cout << "Variables not initalized: ";
    gdc_nmi_1.print();

    // Variables are zero initialized via object initialization
    Gdc_nmi gdc_nmi_2{};
    std::cout << "Variables are zero initialized via object initialization: ";
    gdc_nmi_2.print();

    // Variables are initialized via member variables zero initializations
    Gdc_zmi gdc_zmi;
    std::cout << "Variables are initialized via member variables zero initializations: ";
    gdc_zmi.print();

    // Variables are initialized via member variables initializations
    Gdc_mi gdc_mi;
    std::cout << "Variables are initialized via member variables initializations: ";
    gdc_mi.print();

    std::cout << "---------------------------------------------------------------\n";
    //////////////////////////////////////////////////////////////////////////////////////

    //********** Objects created via default constructor **********
    // Variables not initalized (printing undefined values)
    Mc_nmi mc_nmi_1;
    std::cout << "Variables not initalized: ";
    mc_nmi_1.print();

    // Variables are zero initialized via object initialization
    Mc_nmi mc_nmi_2{};
    std::cout << "Variables are zero initialized via object initialization: ";
    mc_nmi_2.print();

    // Variables are zero initialized via member variables zero initializations
    Mc_zmi mc_zmi;
    std::cout << "Variables are initialized via member variables zero initializations: ";
    mc_zmi.print();

    // Variables are initialized via member variables initializations
    Mc_mi mc_mi;
    std::cout << "Variables are initialized via member variables initializations: ";
    mc_mi.print();

    std::cout << "*****************************************************\n";
    return 0;
}
