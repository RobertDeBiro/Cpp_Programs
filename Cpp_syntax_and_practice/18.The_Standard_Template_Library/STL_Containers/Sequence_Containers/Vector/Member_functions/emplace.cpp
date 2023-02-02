/*
 * emplace(const_iterator pos, Args&&... args) -> iterator
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/container/vector/emplace
 */

#include <iostream>
#include <string>
#include <vector>

struct A {
    std::string s;

    A(std::string str) : s(std::move(str)) { std::cout << "\tConstructed\n"; }
    A(const A& o) : s(o.s) { std::cout << "\tCopy constructed\n"; }
    A(A&& o) : s(std::move(o.s)) { std::cout << "\tMove constructed\n"; }

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

    // Create empty vector of "A" objects and reserve enough place so vector does not have to resize
    std::vector<A> container;
    container.reserve(10);

    // Everything in this program could be done also with insert() function, except following part
    //  - insert() cannot insert char literal into A constructor
    std::cout << "Emplace:\n";
    container.emplace(container.end(), "one");
    std::cout << "------------------------------------\n";

    std::cout << "Construct 2 \"A\" objects:\n";
    A two { "two" }, three { "three" };

    std::cout << "Emplace with A&:\n";
    container.emplace(container.end(), two);
    std::cout << "Emplace with A&&:\n";
    container.emplace(container.end(), std::move(three));
    std::cout << "------------------------------------\n";

    std::cout << "Vector content: ";
    printVector(container);

    std::cout << "*****************************************************\n";
    return 0;
}