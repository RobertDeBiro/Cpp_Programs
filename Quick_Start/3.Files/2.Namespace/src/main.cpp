/**
 * * Naming collision
 *      - happens when compiler or linker can't distinguish between global variables or functions
 *      - most naming collistions occur in two cases:
 *          1. Two (or more) definitions for a function (or global variable) are introduced into separate 
 *             files that are compiled into the same program
 *          2. Two (or more) definitions for a function (or global variable) are introduced into the same
 *             file (often via #include)
 **/
/**
 * * Namespace
 *      - region that allows us to declare names inside of it for the purpose of disambiguation
 *      - provides namespace scope
 *      - within a namespace, all names must be unique
 **/
/**
 * * Global namespaces
 *      - any name that is not defined inside a class, function, or a namespace is considered to be part of
 *        an implicitly defined namespace called the global namespace
 **/
/**
 * * std namespace
 *      - std (short for standard) is namespace created within C++ standard library
 *      - two different ways to use std namespace:
 *          1. Explicit namespace qualifier std::
 *?              std::cout;
 *          2. Using namespace std
 *?              using namespace std;
 *?              cout;
 **/

#include <iostream>

// void funct(int x)
// {
//     std::cout << "Hello from function!" << std::endl;
// }

using namespace std;

int main()
{
    // std::cout << "Namespace chapter!" << std::endl;
    cout << "Namespace chapter!" << endl;

    return 0;
}