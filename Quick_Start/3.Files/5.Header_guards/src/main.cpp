/**
 * * Header guards
 *      - also called include guard
 *      - conditional compilation directives
 *          - ifdef
 *              - allow the preprocessor to check whether an identifier has been previously #defined
 *          - ifndef
 *              - opposite of ifdef
 *          - endif
 *              - encloses ifdef or ifndef
 *      - prevent a given header file from being #included more than once in the same file
 **/

#include <iostream>
#include "../inc/add.hpp"
#include "../inc/random.hpp"

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}