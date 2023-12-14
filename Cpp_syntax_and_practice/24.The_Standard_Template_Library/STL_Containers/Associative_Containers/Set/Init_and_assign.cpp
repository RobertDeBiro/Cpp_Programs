#include <iostream>
#include <set>

// User-defined data type
class Person
{
public:
    int age{};
    std::string name{};

    //* operator for 'std::less' implementation (default)
    bool operator< (const Person& rhs) const { return age < rhs.age; }

    //* operator for 'std::greater' implementation
    bool operator> (const Person& rhs) const { return age > rhs.age; }
};

// Function template
template <typename T>
void printSet(T varSet)
{
    for(auto elem : varSet)
        std::cout << elem << ' ';
    std::cout << '\n';
}

// Overloading function template 1
void printSet(std::set<Person> varSet)
{
    for(auto elem : varSet)
        std::cout << elem.name << ' ' << elem.age << '\n';
}

// Overloading function template 2
void printSet(std::set<Person, std::greater<>> varSet)
{
    for(auto elem : varSet)
        std::cout << elem.name << ' ' << elem.age << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    //* Initialize 'set' in default ascending order
    std::set<int> varSet1{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "Initial set container: \n";
    printSet(varSet1);

    //* Initialize 'set' in default ascending order, explicitly using 'std::less<>'
    std::set<int, std::less<>> varSet2{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "std::less set container: \n";
    printSet(varSet1);

    //* Initialize 'set' in descending order
    std::set<int, std::greater<>> varSet3{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "std::greater set container: \n";
    printSet(varSet3);

    std::cout << "---------------------------\n";

    //* User defined data in 'std::set' container:
    //  - in order to declare user-defined 'std::set' container, we need to tell to the
    //    'std::set' how to compare the elements and sort them
    //  - we do that by using overload operator inside user-defined data type
    std::set<Person> varSet4{ {4, "Luka"}, {29, "Martina"}, {2, "Toma"} };
    std::cout << "user-defined data set container: \n";
    printSet(varSet4);

    std::cout << "---------------------------\n";

    std::set<Person, std::greater<>> varSet5{ {4, "Luka"}, {29, "Martina"}, {2, "Toma"} };
    std::cout << "std::greater user-defined data set container: \n";
    printSet(varSet5);

    std::cout << "*****************************************************\n";
    return 0;
}
