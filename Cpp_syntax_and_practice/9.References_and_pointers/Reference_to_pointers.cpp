#include <iostream>

int main()
{
    int i = 5;
    int* p = &i;
    std::cout << "&i = " << &i << '\n';
    std::cout << "p = " << p << '\n';

    /*
     * Initialize reference to pointer, with a pointer
     */ 
    int *&r1 = p;
    std::cout << "r1 = " << r1 << '\n';

    std::cout << "-----------------------\n";

    /*
     * Assign reference to pointer, with an address
     */ 
    int j = 10;
    r1 = &j;
    std::cout << "&i = " << &i << '\n';
    std::cout << "j = " << &j << '\n';
    std::cout << "p = " << p << '\n';
    std::cout << "r1 = " << r1 << '\n';

    /*
     * Initialize reference to a poitner, with an address
     *  - ERROR: cannot initialize non-const lvalue reference of type int*&
     *           with an rvalue of type int*
     *  - pointer variable is lvalue, object address is rvalue!
     */ 
    int k = 20;
    //int *&r2 = &k;

    std::cout << "-----------------------\n";
    
    /*
     * Initialize reference to const pointer, with an address
     *  - with this construct we can initialize non-const lvalue reference of type int*&
     *    with an rvalue of type int*
     */
    int *const &r3 = &k;
    std::cout << "&k = " << &k << '\n';
    std::cout << "r3 = " << r3 << '\n';

    return 0;
}