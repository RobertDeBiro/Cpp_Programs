#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    int i = 5;
    int* p = &i;
    std::cout << "&i = " << &i << '\n';
    std::cout << "p = " << p << '\n';

    //********** Initialize "reference to pointer" with "pointer variable" **********
    int*& r1 = p;
    std::cout << "p = " << p << '\n';
    std::cout << "r1 = " << r1 << '\n';

    std::cout << "-----------------------\n";

    //********** Assign "reference to pointer" with "variable address" **********
    int j = 10;
    r1 = &j;

    std::cout << "&i = " << &i << '\n';
    std::cout << "&j = " << &j << '\n';
    std::cout << "p = " << p << '\n';
    std::cout << "r1 = " << r1 << '\n';

    //********** Initialize "reference to pointer" with "variable address" **********
    // ERROR: cannot initialize non-const lvalue reference of type 'int*&' with an rvalue of type 'int*'
    // - non-const reference needs to be initialized with modifyable lvalue object
    // - pointer variable is lvalue, object address is rvalue
    int k = 20;
    //!int*& r2 = &k;

    std::cout << "-----------------------\n";

    //********** Initialize "reference to const pointer" with "variable address" **********
    // - with this construct we can initialize non-const lvalue reference of type 'int*&'
    //   with an rvalue of type 'int*'
    int *const &r3 = &k;
    std::cout << "&k = " << &k << '\n';
    std::cout << "r3 = " << r3 << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}