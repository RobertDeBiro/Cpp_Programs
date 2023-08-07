#include <iostream>

struct Employee
{
    int id{};
    int age{};
};

int main()
{
    Employee alan{ 1, 34 };

    Employee* ptr{ &alan };

    // std::cout << *ptr.id << '\n'; //! ERROR - doesn't work, "." has bigger precedence than "*"
    std::cout << (*ptr).id << '\n'; // Works, but not so pretty
    std::cout << ptr->age << '\n'; // Most appropriate - using arrow operator

    return 0;
}