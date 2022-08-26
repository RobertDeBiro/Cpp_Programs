#include <iostream>
#include <functional>

int division(int x, int y)
{
    return x / y;
}

int main()
{
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

    // Parameters are already binded
    auto fcnPtrBind{ std::bind(&division, x, y) };
    std::cout << "The division from fcnPtrBind is: " << fcnPtrBind() << std::endl;

    // Requires 2 input parameters (the same as first example, without std::bind)
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
    auto fcnPtrBindPh1{ std::bind(&division, std::placeholders::_1, y) };
    std::cout << "The division from fcnPtrBindPh1 is: " << fcnPtrBindPh1(x) << std::endl;

    // Following won't work - std::placeholders::_2 can't be called without _1
    //auto fcnPtrBindPh2{ std::bind(&division, x, std::placeholders::_2) };

    return 0;
}
