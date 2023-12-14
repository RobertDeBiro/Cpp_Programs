#include <iostream>
#include <string>
#include <vector>

struct A {
    std::string s;

    A(std::string str) : s(std::move(str)) { std::cout << "\tConstructed\n"; }
    A(const A& o) : s(o.s) { std::cout << "\tCopy constructed\n"; }
    A(A&& o) : s(std::move(o.s)) { std::cout << "\tMove constructed\n"; }

    // Neither copy assignment operator or move assignment operator needs to be invoked as part of
    // this program, but it is mandatory to define either one of them.
    // The reason for this behavior is related to the rule of special member function generation in C++.
    // The compiler will automatically generate default versions of the copy constructor, copy assignment operator,
    // move constructor, and move assignment operator if they are not explicitly declared.
    // However, if we provide a user-defined version of any of these special member functions, the compiler will not
    // generate the corresponding default version.
    // However, if we provide a user-defined move assignment operator, the compiler does not generate the default copy assignment operator.
    // Similarly, if we provide a user-defined copy assignment operator, the compiler does not generate the default move assignment operator.
    // This behavior is to prevent unintended usage of these operations, as their presence may indicate specific ownership transfer semantics.
    // If both the copy assignment operator and the move assignment operator are missing, the compiler attempts to use the deleted default versions
    // of these operators, which results in a compilation error.
    // By providing at least one of these assignment operators, we explicitly define the desired behavior for assignment operations,
    // and the compiler does not generate the deleted default versions.
    // - in general, here it is good to use "Rule of Five" and define everything
    A& operator=(const A& other) {
        s = other.s;
        std::cout << "\tCopy assigned\n";
        return *this;
    }
    A& operator=(A&& other) {
        s = std::move(other.s);
        std::cout << "\tMove assigned\n";
        return *this;
    }
};

void printVector(const std::vector<A>& varVect)
{
    for(const auto& elem : varVect)
        std::cout << elem.s << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    // Create empty vector of 'A' objects and reserve enough place so vector does not have to resize
    std::vector<A> container;
    container.reserve(10);

    //* Emplace char literal
    //  - cannot be done via 'insert()'
    //  - 'insert()' cannot insert char literal, it can only insert class objects
    std::cout << "Emplace:\n";
    container.emplace(container.end(), "one");
    std::cout << "------------------------------------\n";

    std::cout << "Construct 2 \"A\" objects:\n";
    A two { "two" }, three { "three" };

    //* Emplace class object
    std::cout << "Emplace with A&:\n";
    container.emplace(container.end(), two);

    //* Emplace R-value class object by using std::move
    std::cout << "Emplace with A&&:\n";
    container.emplace(container.end(), std::move(three));

    std::cout << "------------------------------------\n";

    std::cout << "Vector content: ";
    printVector(container);

    std::cout << "*****************************************************\n";
    return 0;
}