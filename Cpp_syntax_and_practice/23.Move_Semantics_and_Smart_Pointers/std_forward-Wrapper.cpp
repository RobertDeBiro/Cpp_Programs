/*
 * template< typename T >
 * forward( typename std::remove_reference<T>::type& t ) noexcept -> T&&
 *
 *  - forwards lvalues as either lvalues or as rvalues, depending on T
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/utility/forward
 */

#include <iostream>
#include <utility>

struct S{};

void f(S& s) { std::cout << "f(S&)" << std::endl; } // Receiving l-value reference
void f(S&& s) { std::cout << "f(S&&)" << std::endl; } // Receiving r-value reference

// In following wrappers, 's' is typed either as l-value reference, or r-value reference,
// but 's' object itself is an l-value, i.e. when using 's' object, it acts like a normal l-value object
void wrap1(S& s) { f(s); } // calls 'f(S& s)'
void wrap1(S&& s) { f(s); } // calls 'f(S& s)'

// In following syntax, by using 'std::forward' function, 't' remains r-value if it received r-value, 
// and l-value if it received l-value
// - 'std::forward' must be called within template function that receives r-value references
template<typename T>
void wrap2(T&& t) { f(std::forward<T>(t)); }

int main()
{
    std::cout << "*****************************************************\n";

    S s;

    //* Send l-value to function 'f'
    // - 'f(S& s)' called
    f(s);

    //* Send r-value to function 'f'
    // - 'f(S&& s)' called
    f(S());

    ////////////////////////////////////////////////////////////
    std::cout << "-------------------------------------------\n";

    //* Send l-value to function 'wrap1'
    // - 'wrap1(S& s)' called
    wrap1(s);

    //* Send r-value to function 'wrap1'
    // - 'wrap1(S&& s)' called
    wrap1(S());

    ////////////////////////////////////////////////////////////
    std::cout << "-------------------------------------------\n";
    
    wrap2(s);
    wrap2(S());

    std::cout << "*****************************************************\n";
    return 0;
}