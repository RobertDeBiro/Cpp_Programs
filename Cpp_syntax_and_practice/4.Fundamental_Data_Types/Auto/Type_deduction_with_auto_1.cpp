#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    int i = 0, &r = i;
    
    /*
     * 'auto' object initialized with reference
     *  - when we use a reference as an initializer, the initializer is the referenced object
     *    (in this example object 'i')
     *  - hence 'auto' will be deduced as 'int', and 'a' variable will be 'int'
     */
    auto a = r;     // 'a' is an 'int'

    ////////////////////////////////////////////////////////////////////////////////////

    /*
     * 'auto' object with top-level and low-level consts
     *  - 'auto' ordinarily ignores top-level const (just like other objects, such as pointers)
     */
    const int ci = i, &cr = ci;
    auto b = ci;    // 'b' is an 'int'
    auto c = cr;    // 'c' is an 'int'
    auto d = &i;    // 'd' is an 'int*'
    auto e = &ci;   // 'e' is an 'const int*'

    // If we want the deduced type to have a top-level const, we must say so explicitly
    //  - in previous example, variable 'b' ignores top-level const
    const auto f = ci;  // 'f' is a 'const int'

    /*
     * 'auto'-deduced reference with top-level and low-level consts
     *  - when we ask for a reference to an auto-deduced type, top-level consts in the initializer are not
     *    ignored
     */
    auto &g = ci; // 'g' is an 'const int&'
    
    ////////////////////////////////////////////////////////////////////////////////////

    /*
     * 'auto'-deduced reference to a literal
     */
    // auto &h = 42; // ERROR: we cannot bind reference to a literal
    const auto &j = 42; // we can bind const reference to a literal

    /*
     * Base 'auto'-deduced type with multiple declarators
     *  - reference and pointer is part of a particular declarator and not part of the
     *    base type for the declaration
     */
    auto k = ci, &l = i;    // k is an 'int', l is "int&"
    auto &m = ci, *p = &ci; // m is an "const int&", p is "const int*"
    // auto &n = i, *p2 = &ci; // error: n is "int&", whereas p2 is "conts int*, which are two different base types" 

    /*
    * C++ Primer
    * Exercises section 2.5.2
    *  - Exercise 2.33
    */
    a = 42;     // OK: a is an 'int'
    std::cout << "a = " << a << '\n';
    
    b = 42;     // OK: b is an 'int'
    std::cout << "b = " << b << '\n';

    c = 42;     // OK: c is an 'int'
    std::cout << "c = " << c << '\n';

    //d = 42;   // ERROR: d is an "int*" - we cannot assign literal to pointer

    //e = 42;   // ERROR: e is an "const int*" - we cannot assign literal to pointer

    //g = 42;   // ERROR: g is an "const int&" - we cannot change reference to const

    std::cout << "*****************************************************\n";
    return 0;
}