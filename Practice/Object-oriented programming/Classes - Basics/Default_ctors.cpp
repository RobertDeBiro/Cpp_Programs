// Constructors

#include <iostream>
#include <vector>

class Def1
{
    int m_x;
    int m_y;
public:
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

class Def2
{
    int m_x{};
    int m_y{};
public:
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

class Def3
{
    int m_x{ 2 };
    int m_y{ 5 };
public:
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

// Since in following class we created constructor, if we want to use default one, we need to create it
// (whereas with other previous classes that wasn't needed)
class Def4
{
    int m_x;
    int m_y;
public:
    Def4() = default;
    Def4(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

class Def5
{
    int m_x{};
    int m_y{};
public:
    Def5() = default;
    Def5(int x, int y)
    {
        m_x = x;
        m_y = y;
        std::cout << "Constructor is called for Def5!\n";
    }
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

class Def6
{
    int m_x;
    int m_y;
public:
    Def6()
    {
        std::cout << "Constructor is called even though no value is assigned to object!\n";
    }
    void print() { std::cout << m_x << ' ' << m_y << '\n'; }
};

int main()
{
    // Def1, Def2 and Def3 are using generated default constructor
    //  - default constructor is generated only when our class doesn't contain any other constructor
    //  - when using generated default constructor, member variables can be initialized if using one of the following implementations:
    //    1) Object initialization
    //         - def1_b{}
    //         - this requires only zero initialization - if object is initialized with some values, since member variables are private
    //           compiler error will appear (def2_b example)
    //    2) non-static member initialization
    //         - def2, def3
    //         - member variables can be both zero-initialized or initialized with some values, it doesn't matter
    //  - def1_a doesn't have neither object initialization or non-static member initialization, and therefore variables are not initialized with default constructor

    Def1 def1_a;
    def1_a.print(), // prints some garbage
    std::cout << "******************************\n";

    Def1 def1_b{};
    def1_b.print(); // variables are zero initialized via default constructor, by using object instantiation
    std::cout << "******************************\n";

    Def2 def2;
    def2.print(); // variables are initialized via default constructor, by using member variables zero initializations
    std::cout << "******************************\n";

    // Def2 def2_b{2, 5};
    // def2_b.print(); // This produces error because default constructor can only receive zero initialization
    // std::cout << "******************************\n";

    Def3 def3;
    def3.print(); // variables are initialized via default constructor, by using member variables initializations
    std::cout << "******************************\n";

    Def4 def4{};
    def4.print(); // variables are zero initialized via default constructor (the same as for def1_b)
    std::cout << "******************************\n";

    Def5 def5;
    def5.print(); // variables are zero initialized via default constructor (the same as for def2)
    std::cout << "******************************\n";

    Def6 def6; // Checking that constructor is called as soon object is instantiated
    std::vector<Def6> vecDef6a; // When container object is instantiated, typed with some class, constructor won't be called
    std::vector<Def5> vecDef5b { {1, 2} }; // When container object is instantiated, and fulfilled with class object, constructor will be called
    std::cout << "******************************\n";

    return 0;
}
