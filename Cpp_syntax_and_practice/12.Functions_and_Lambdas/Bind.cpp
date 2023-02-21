/*
 * template< class F, class... Args >
 * bind( F&& f, Args&&... args );
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/utility/functional/bind
 *  - https://stackoverflow.com/questions/6610046/stdfunction-and-stdbind-what-are-they-and-when-should-they-be-used
 *  - https://stackoverflow.com/questions/47532424/usage-of-this-pointer-in-stdbind
 */

#include <iostream>
#include <functional>

int division(int x, int y)
{
    return x / y;
}

int main()
{
    std::cout << "*****************************************************\n";

    int x, y;
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter y: ";
    std::cin >> y;
    std::cout << "The division is: " << division(x, y) << std::endl;

    // Types of function pointer declaration syntaxes:
    //  1) int (*div_fcnPtr)(int, int){ &division }
    //  2) std::function<int(int,int)> div_fcnPtr{ &division }
    //  3) auto div_fcnPtr{ &division }

    // Requires 2 input parameters
    auto fcnPtrNormal{ division };
    std::cout << "The division from fcnPtrNormal is: " << fcnPtrNormal(x, y) << std::endl;

    // Bind x and y parameters
    auto fcnPtrBind{ std::bind(&division, x, y) };
    std::cout << "The division from fcnPtrBind is: " << fcnPtrBind() << std::endl;

    // Requires 2 input parameters (the same as first example that doesn't contain std::bind)
    // - 1. fcnPtrBindPh12 input parameter = 1. division input parameter
    // - 2. fcnPtrBindPh12 input parameter = 2. division input parameter
    auto fcnPtrBindPh12{ std::bind(&division, std::placeholders::_1, std::placeholders::_2) };
    std::cout << "The division from fcnPtrBindPh12 is: " << fcnPtrBindPh12(x, y) << std::endl;

    // Requires 2 input parameters
    // - 1. fcnPtrBindPh12 input parameter = 2. division input parameter
    // - 2. fcnPtrBindPh12 input parameter = 1. division input parameter
    auto fcnPtrBindPh21{ std::bind(&division, std::placeholders::_2, std::placeholders::_1) };
    std::cout << "The division from fcnPtrBindPh21 is: " << fcnPtrBindPh21(x, y) << std::endl;

    // Requires only first input parameter, second is binded
    auto fcnPtrBindPh1a{ std::bind(&division, std::placeholders::_1, y) };
    std::cout << "The division from fcnPtrBindPh1 is: " << fcnPtrBindPh1a(x) << std::endl;

    // ERROR:
    // we cannot declare std::placeholders::_2 if we didn't declare std::placeholders::_1
    //auto fcnPtrBindPh2{ std::bind(&division, x, std::placeholders::_2) };
    
    // Add division(x, std::placeholders::_1) to fcnPtrBindPh1b(var)
    //  - First (and only) fcnPtrBindPh1b parameter will be added as second division parameter
    auto fcnPtrBindPh1b{ std::bind(&division, x, std::placeholders::_1) };
    std::cout << "The division from fcnPtrBindPh1 is: " << fcnPtrBindPh1b(x) << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}
