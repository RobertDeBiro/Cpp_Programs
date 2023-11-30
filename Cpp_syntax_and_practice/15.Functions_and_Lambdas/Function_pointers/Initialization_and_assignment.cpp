#include <iostream>
#include <string>
#include <functional>

void randFunct1()
{
    std::cout << "randFunct1!\n";
}

int randFunct2(int x, int y)
{
    int z = x * y;
    std::cout << "randFunct2!\n";
    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';
    std::cout << "z = " << z << '\n';
    return y;
}

void randFunct3(std::string s)
{
    std::cout << "randFunct3!\n";
    std::cout << s << '\n';
}

int randFunct4(int x, int y)
{
    int z = x + y;
    std::cout << "randFunct4!\n";
    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';
    std::cout << "z = " << z << '\n';
    return y;
}

int main()
{
    std::cout << "*****************************************************\n";

    //********** Initialization using "pointer syntax" **********
    //  - return: void
    //  - parameters: none
    //  - using "&" with function name
    void (*fcnPtr1)(){ &randFunct1 };
    fcnPtr1();

    std::cout << "-------------------------\n";

    //  - return: int
    //  - parameters: (int, int)
    int (*fcnPtr2a)(int, int){ randFunct2 };
    int x = 1, y = 2;
    fcnPtr2a(x, y);

    std::cout << "-------------------------\n";
    ////////////////////////////////////////////////////////////////////////////

    //********** Initialization using 'std::function' **********
    std::function<int(int, int)> fcnPtr2b{ randFunct2 };
    fcnPtr2b(3, 4);

    std::cout << "-------------------------\n";

    // Initialize it with other function pointer
    std::function<int(int, int)> fcnPtr2c{ fcnPtr2b };
    fcnPtr2c(5, 6);

    std::cout << "-------------------------\n";
    ////////////////////////////////////////////////////////////////////////////

    //********** Initialization using 'auto' **********
    auto fcnPtr3{ randFunct3 };
    fcnPtr3("HelloWorld!");

    std::cout << "-------------------------\n";
    ////////////////////////////////////////////////////////////////////////////

    //********** Assign funct ptr with another funct ptr **********
    std::function<int(int, int)> fcnPtr4a{ randFunct4 };
    std::function<int(int, int)> fcnPtr4b;
    fcnPtr4b = fcnPtr4a;
    fcnPtr4b(7, 8);

    std::cout << "-------------------------\n";
    ////////////////////////////////////////////////////////////////////////////

    //********** Alias for function pointer data type **********
    using fnctPtrAssig = int(*)(int, int);
    fnctPtrAssig fcnPtr4c{ randFunct4 };
    fcnPtr4c(9, 10);

    std::cout << "*****************************************************\n";
    return 0;
}