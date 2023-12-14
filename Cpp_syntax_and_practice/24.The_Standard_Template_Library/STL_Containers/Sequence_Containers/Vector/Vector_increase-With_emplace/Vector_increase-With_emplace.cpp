#include <iostream>
#include <string>
#include <vector>

struct A {
    std::string s;

    A(std::string str) : s(std::move(str))
    {
        std::cout << "\tConstructed = " << s << '\n';
    }

    A(const A& o) : s(o.s)
    {
        std::cout << "\tCopy constructed = " << s << '\n';
    }

    A(A&& o) : s(std::move(o.s))
    {
        std::cout << "\tMove constructed = " << s << '\n';
    }

    A& operator=(const A& other) {
        s = other.s;
        std::cout << "\tCopy assigned: = " << s << '\n';
        return *this;
    }
    A& operator=(A&& other) {
        s = std::move(other.s);
        std::cout << "\tMove assigned = " << s << '\n';
        return *this;
    }
};

void printVector(const std::vector<A>& varVect)
{
    for(const auto& elem : varVect)
        std::cout << elem.s << ' ';
    std::cout << '\n';
}

void printVectorSizeAndCapacity(const std::vector<A>& varVect)
{
    std::cout << "Size: " << varVect.size() << "   Capacity: " << varVect.capacity() << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    // Create empty vector of 'A' objects
    std::vector<A> container;
    
    // TODO
    //container.reserve(1);
    //container.reserve(10);

    //* Emplace 'const char*' literal at the end of the vector
    // - vector member function 'emplace()' constructs object inside vector
    //   - hence, following statement calls 'A' "constructor"!
    // - everything in this program could be done also with 'insert()' function, except following part
    //   - 'insert()' cannot insert char literal into A constructor
    std::cout << "Emplace:\n";
    container.emplace(container.end(), "one");
    printVectorSizeAndCapacity(container);
    std::cout << "------------------------------------\n";

    //* Construct two 'A' objects
    // - constructor is called twice
    std::cout << "Construct 2 \"A\" objects:\n";
    A three { "three" }, five { "five" };
    std::cout << "------------------------------------\n";

    //* Emplace struct object at the end of the vector
    // - always when we emplace class or structure, "copy constructor" is called
    // - since vector will be increased, it needs to be coppied to a new memory location
    //   and all objects that are parts of the vector will be constructed again
    // - hence, following statements will call two 'A' "copy constructors": one for existing element
    //   and one for emplaced element
    // - vector capacity is increased to '2' (double of previous capacity, which was '1')
    std::cout << "Emplace with A&:\n";
    container.emplace(container.end(), three);
    printVectorSizeAndCapacity(container);
    std::cout << "------------------------------------\n";

    //* Emplace struct object at the end of the vector by using 'std::move()'
    // - once more vector is coppied to new memory location in order to be able to increase
    // - for object emplaced with 'std::move()' "move constructor" is called whereas
    //   for existing two 'A' objects copy constructor is called
    // - vector capacity is increased to '4'
    std::cout << "Emplace with A&&:\n";
    container.emplace(container.end(), std::move(five));
    printVectorSizeAndCapacity(container);
    std::cout << "------------------------------------\n";

    //* Emplace 'const char*' literal at the beginning of the vector
    // - in this stage we have vector of 'A' objects with size of '3' and capacity of '4'
    // - since we are emplacing 'const char*' literal, "constructor" is called
    // - because 'container.begin()' is already taken, we couldn't just construct object by calling "constructor", but rather
    //   in addition we needed also to move created object into vector
    //   - since newly created object is moving into beginning of the vector, where we already had 'A' object, "move assignment"
    //     will be called
    // - since vector have sufficient capacity for the new object, vector doesn't need to copy existing objects,
    //   but rather just move them
    // - last element ('five') is moving to a place in vector which was empty, hence "move constructor" will be called 
    std::cout << "Emplace at the container[0]:\n";
    container.emplace(container.begin(), "zero");
    printVectorSizeAndCapacity(container);
    std::cout << "------------------------------------\n";

    //* Construct two 'A' objects
    std::cout << "Construct 2 more \"A\" objects:\n";
    A two{ "two" }, four{ "four" };
    std::cout << "------------------------------------\n";

    std::cout << "Emplace at the container[2]\n";
    container.emplace((container.begin() + 2), two);
    printVectorSizeAndCapacity(container);
    std::cout << "------------------------------------\n";

    std::cout << "Emplace at the container[4]:\n";
    container.emplace((container.begin() + 4), std::move(four));
    printVectorSizeAndCapacity(container);
    std::cout << "------------------------------------\n";

    std::cout << "Vector content: ";
    printVector(container);

    std::cout << "*****************************************************\n";
    return 0;
}

// If we would at the beginning of the program reserve some amount of space for vector, vector wouldn't have to copy elements
// at all, only move them
// - good example in program ../Member_functions//emplace.cpp
