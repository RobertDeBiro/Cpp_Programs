// References:
//  - https://en.cppreference.com/w/cpp/utility/functional/bind
//  - https://stackoverflow.com/questions/6610046/stdfunction-and-stdbind-what-are-they-and-when-should-they-be-used
//  - https://stackoverflow.com/questions/47532424/usage-of-this-pointer-in-stdbind

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

    //********** Assign function pointer to 'division' function **********
    //  - 'fcnPtrNormal' requires every parameter as input
    auto fcnPtrNormal{ division };
    std::cout << "The division from fcnPtrNormal is: " << fcnPtrNormal(x, y) << std::endl;

    /////////////////////////////////////////////////////////////////////////////

    //********** Bind function with x and y parameters **********
    //  - 'fcnPtrBind' doesn't require parameters as input
    auto fcnPtrBind{ std::bind(&division, x, y) };
    std::cout << "The division from fcnPtrBind is: " << fcnPtrBind() << std::endl;

    /////////////////////////////////////////////////////////////////////////////

    //********** Bind function with two placeholders **********
    // 'fcnPtrBindPh12' requires every parameter as input:
    //  - 1. 'fcnPtrBindPh12' input parameter = 1. division input parameter
    //  - 2. 'fcnPtrBindPh12' input parameter = 2. division input parameter
    auto fcnPtrBindPh12{ std::bind(&division, std::placeholders::_1, std::placeholders::_2) };
    std::cout << "The division from fcnPtrBindPh12 is: " << fcnPtrBindPh12(x, y) << std::endl;

    // Placeholders placed in opposite direction
    // 'fcnPtrBindPh21' requires every parameter as input:
    // - 1. 'fcnPtrBindPh21' input parameter = 2. division input parameter
    // - 2. 'fcnPtrBindPh21' input parameter = 1. division input parameter
    auto fcnPtrBindPh21{ std::bind(&division, std::placeholders::_2, std::placeholders::_1) };
    std::cout << "The division from fcnPtrBindPh21 is: " << fcnPtrBindPh21(x, y) << std::endl;

    /////////////////////////////////////////////////////////////////////////////

    //********** Bind function with only one placeholders **********
    // 'fcnPtrBindPh1a' requires only first parameter as input
    auto fcnPtrBindPh1a{ std::bind(&division, std::placeholders::_1, y) };
    std::cout << "The division from fcnPtrBindPh1 is: " << fcnPtrBindPh1a(x) << std::endl;

    // We cannot use 'std::placeholders::_2' if we didn't use 'std::placeholders::_1'
    //! auto fcnPtrBindPh2{ std::bind(&division, x, std::placeholders::_2) };

    // There is no problem with using 'std::placeholders::_1' for second parameter in 'std::bind'
    // function
    //  - with that we are telling that first parameter send inside 'fcnPtrBindPh1b' function call
    //    (in this example only one is send) will be assigned to second 'division' parameter (to 'y')
    auto fcnPtrBindPh1b{ std::bind(&division, x, std::placeholders::_1) };
    std::cout << "The division from fcnPtrBindPh1 is: " << fcnPtrBindPh1b(x) << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}
