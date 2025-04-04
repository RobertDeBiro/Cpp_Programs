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

    //********** std::bind - Bind function with x and y parameters **********
    //  - 'fcnPtrBind' doesn't require parameters as input
    auto fcnPtrBind{ std::bind(&division, x, y) };
    std::cout << "The division from fcnPtrBind is: " << fcnPtrBind() << std::endl;

    //********** std::bind_front - Bind function with x and y parameters **********
    //  - when we are not using 'std::placeholders', it is the same as 'std::bind'
    auto fcnPtrBindFront{ std::bind_front(&division, x, y) };
    std::cout << "The division from fcnPtrBindFront is: " << fcnPtrBindFront() << std::endl;

    /////////////////////////////////////////////////////////////////////////////

    //********** std::bind - Bind function with two placeholders **********
    // - 'fcnPtrBindPh12' requires every parameter as input:
    //   - 1. 'fcnPtrBindPh12' input parameter = 1. division input parameter
    //   - 2. 'fcnPtrBindPh12' input parameter = 2. division input parameter
    auto fcnPtrBindPh12{ std::bind(&division, std::placeholders::_1, std::placeholders::_2) };
    std::cout << "The division from fcnPtrBindPh12 is: " << fcnPtrBindPh12(x, y) << std::endl;

    // Placeholders placed in opposite direction
    // - 'fcnPtrBindPh21' requires every parameter as input:
    //   - 1. 'fcnPtrBindPh21' input parameter = 2. division input parameter
    //   - 2. 'fcnPtrBindPh21' input parameter = 1. division input parameter
    auto fcnPtrBindPh21{ std::bind(&division, std::placeholders::_2, std::placeholders::_1) };
    std::cout << "The division from fcnPtrBindPh21 is: " << fcnPtrBindPh21(x, y) << std::endl;

    //********** std::bind_front - Bind function with two placeholders **********
    //! std::bind_front' cannot be used in situations when we need multiple 'std::placeholders'

    /////////////////////////////////////////////////////////////////////////////

    //********** std::bind - Bind function with only one placeholders **********
    // - 'fcnPtrBindPh1a' requires only first parameter as input
    //   - only in this case it is better to use 'std::bind_front'
    auto fcnPtrBindPh1a{ std::bind(&division, std::placeholders::_1, y) };
    std::cout << "The division from fcnPtrBindPh1 is: " << fcnPtrBindPh1a(x) << std::endl;

    // We cannot use 'std::placeholders::_2' if we didn't use 'std::placeholders::_1'
    //! auto fcnPtrBindPh2{ std::bind(&division, x, std::placeholders::_2) };

    // There is no problem with using 'std::placeholders::_1' for second parameter in 'std::bind' function
    //  - with that we are telling that first parameter send inside 'fcnPtrBindPh1b' function call
    //    (in this example only one is send) will be assigned to second 'division' parameter (to 'y')
    auto fcnPtrBindPh1b{ std::bind(&division, x, std::placeholders::_1) };
    std::cout << "The division from fcnPtrBindPh1 is: " << fcnPtrBindPh1b(y) << std::endl;

    //********** std::bind_front - Bind function with only one placeholders **********
    // - basically, the best use case to use 'bind_front' is when we want to bind only one (or only first) parameter
    auto fcnPtrBindFrontPh1a{ std::bind_front(&division, y) };
    std::cout << "The division from fcnPtrBindFrontPh1a is: " << fcnPtrBindFrontPh1a(x) << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}
