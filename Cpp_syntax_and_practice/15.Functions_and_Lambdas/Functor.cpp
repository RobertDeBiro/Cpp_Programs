/*
 * Functor
    - an object that works as a function
    - achieved by overloading "operator ()" in some class
    - the benefit is that it saves its state
    - we will use functor if we want to have some class object that can be reassigned by using some
      particular evaluation, such as multiplication
 */

#include <iostream>

class Mul
{
    int _val;

public:
    Mul(){};
    Mul(int val) : _val{ val } {}

    // Everytime we assign a 'Mul' object to some value, the end-result value for will be
    // multiplication of that new value, and the initial one
    int operator() (int val)
    {
        return val * _val;
    }
};

int main()
{
    std::cout << "*****************************************************\n";

    Mul mul12(12);

    //********** Call functor by utilizing operator() **********
    // - even though it looks like 'mult12' changes its value, that is not the case - we fake this by
    //   using 'operator()'
    //    - 'mul12._val' is always equal to the value set inside constructor (in this case '12')
    // - hence we can say that mult12 saves its state

    // Initial value = 12 ; new value = 2 ; result value = 24
    std::cout << mul12(2) << std::endl;

    // Initial value = 12 ; new value = 3 ; result value = 36
    std::cout << mul12(3) << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}