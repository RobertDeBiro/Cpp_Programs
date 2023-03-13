/*
 * Functor
 *  - an object that works as a function
 *  - achieved by overloading "operator ()" in some class
 *  - the benefit is that it saves its state
 *  - we will use functor if we want to have some class object that can be reassigned by using some
 *    particular evaluation, such as multiplication
 */

#include <iostream>

class Mul
{
    int _val;

public:
    Mul(){};
    Mul(int val) : _val{ val } {}

    // Wverytime we assign the object to some value, the end-result value for will be
    // multiplication of that new value, and the initial one
    //  - have in mind that this operator() could be implemented differently
    //  - functor doesn't need to have this kind of behavior
    int operator() (int val)
    {
        return val * _val;
    }
};

int main()
{
    std::cout << "*****************************************************\n";

    Mul mul12(12);

    /*
     * In following example, when I assign new value to my object, my new value will actually be
     * created by using that value and operator() functionality, it won't be assigned as usually
     *  - even though it seems like mult12 has changed its value, it didn't, we faked this by using
     *    operator(), i.e. by using mult12 as a functor
     *  - hence we can say that mult12 saves its state
     */

    // Initial value = 12 ; new value = 2 ; result value = 24
    std::cout << mul12(2) << std::endl;

    // Initial value = 12 ; new value = 3 ; result value = 36
    std::cout << mul12(3) << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}