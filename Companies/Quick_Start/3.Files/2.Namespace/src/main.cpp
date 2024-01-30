//* Naming collision
/**
 *  - happens when compiler or linker can't distinguish between global variables or functions
 *  - most naming collistions occur in two cases:
 *      1. Two (or more) definitions for a function (or global variable) are introduced into separate 
 *         files that are compiled into the same program
 *      2. Two (or more) definitions for a function (or global variable) are introduced into the same
 *         file (often via #include)
 **/

//* Namespace
/**
 *  - region that allows us to declare names inside of it for the purpose of disambiguation
 *  - provides namespace scope
 *  - within a namespace, all names must be unique
 *  - syntax:
 *?     namespace::identifier
 **/

//* Global namespaces
/**
 *  - any name that is not defined inside a function, namespace, or a class is considered to be part of
 *    an implicitly defined namespace called the global namespace
 **/

//* std namespace
/**
 *  - std (short for standard) is namespace created within C++ standard library
 *  - two different ways to use std namespace:
 *      1. Explicit namespace qualifier std::
 *?          std::cout;
 *      2. Using namespace std
 *?          using namespace std;
 *?          cout;
 **/

#include <iostream>

using namespace std;

void funct(int x)
{
    cout << "Hello from function!" << endl;
}

int main()
{
    cout << "Namespace chapter!" << endl;
    funct(5);

    return 0;
}