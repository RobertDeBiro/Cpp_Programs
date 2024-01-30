#include <iostream>
#include <cstdint>

int main()
{
    //* Signed integers
    /**
     *  - holds positive and negative numbers and 0
     *  - integers are signed by default
     *  - overflow results with undefined behavior 
     **/
    short var_s = 3;
	int var_i = -3; // integer signed by default
    long int var_li = 0;
    signed long long var_sll = 1000;

	std::cout << "short var_s = " << var_s << '\n';
	std::cout << "int var_i = " << var_i << '\n';
	std::cout << "long int var_li = " << var_li << '\n';
	std::cout << "signed long long var_sll = " << var_sll << '\n';

    std::cout << "----------------------------------------------------\n";

	// Signed integer overflow will result in undefined behavior
    //  - in this compiler behavior is wrapping, just like with unsigned integers
	var_i = 2'147'483'648; // ' - digit separator
    std::cout << "Positive integer overflow: var_i (2 147 483 648) = " << var_i << '\n';
    var_i = 2'147'483'648 * 2;
	std::cout << "Negative integer overflow: var_i (2 147 483 648 * 2) = " << var_i << '\n';


    // Long long
    var_sll = 2'147'483'648;
    std::cout << "No overflow: var_sll (2 147 483 648) = " << var_sll << '\n';

    //////////////////////////////////////////////////////////////////////////////////////
    
    //* Unsigned integers
    /** 
     *  - holds positive numbers and 0
     *  - cannot overflow but rather it wraps
     *  - if possible should be avoided
     **/
    unsigned int var_ui = -1;
	std::cout << "Unsigned integer wraps and not overflows: var_ui (-1) = " << var_ui << '\n';


    ///////////////////////////////////////////////////////////

    //* Fixed-width integers
    /**
     *  - guarantee to have the same size on any architecture
     *  - accessed including cstdint library
     *  - warning: std::int8_t and std::uint8_t may behave like chars
     **/
    std::uint8_t i{ 70 }; // std::uint8_t is considered as a char type by the compiler
    std::cout << "std::uint8_t is considered as char: i = " << i << std::endl;

    ///////////////////////////////////////////////////////////

    //* size_t
    size_t s = -1;
    std::cout << "size_t s = " << s << std::endl;

	return 0;
}
