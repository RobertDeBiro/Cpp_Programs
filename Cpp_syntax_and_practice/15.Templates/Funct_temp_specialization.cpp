#include <iostream>

// Function template - basic
template <typename T>
void basic_fts(T& i)
{
    std::cout << "Function template" << std::endl;
}

// Function template specialization - basic
template <>
void basic_fts(const int& i)
{
    std::cout << "Function template specialization" << std::endl;
}

// Function template
template<typename T>
void fts_and_overload(T x, T y)
{
    T result{ x + y };
    std::cout << "Function template: x + y = " << result << '\n';
}

// Function template overload with function template
template<typename T>
void fts_and_overload(T x, T y, T z)
{
    T result{ x + y + z };
    std::cout << "Function template overload by other function template: x + y + z = " << result << '\n';
}

// Function template specialization
template<>
void fts_and_overload(double x, double y)
{
    double result{ x + y };
    std::cout << "Function template specialization: x + y = " << result << '\n';
}

// Function template overload with plain function
void fts_and_overload(double x, double y)
{
    double result{ x + y };
    std::cout << "Function template overload by plain function: x + y = " << result << '\n';
}

// Wrapper function for calling function template
template<typename T>
void wrapperFtso(T x, T y)
{
    std::cout << "Wrapper: ";
    fts_and_overload(x, y);
}


void basic_func_temp_specialization()
{
    int i = 1;
    const int j = 1;
    
    basic_fts(i); // Calls "Function template"
    basic_fts(j); // Calls "Function template specialization" because we sent variable of "const int" type

    std::cout << "------------------------------\n";
}


void specialization_and_overload()
{
    int x1{ 1 };
    int y1{ 2 };
    fts_and_overload(x1, y1);

    int z1{ 3 };
    fts_and_overload(x1, y1, z1);

    double x2{ 1.5 };
    double y2{ 2.0 };
    fts_and_overload<double>(x2, y2);
    fts_and_overload(x2, y2);

    wrapperFtso(x1, y1);
    wrapperFtso(x2, y2);

    std::cout << "------------------------------\n";
}


int main()
{
    std::cout << "*****************************************************\n";

    basic_func_temp_specialization();

    specialization_and_overload();

    std::cout << "*****************************************************\n";

    return 0;
}
