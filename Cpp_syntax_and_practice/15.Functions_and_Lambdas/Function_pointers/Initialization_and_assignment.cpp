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

    /*
     * Initializations
     *  1) Using "pointer syntax"
     *  2) Using "std::function"
     *  3) Using "auto"
     */

    // 1)
    // Return: void
    // Parameters: none
    // Using "&" with function name
    void (*fcnPtr1)(){ &randFunct1 };
    fcnPtr1();

    std::cout << "-------------------------\n";

    // Return: int
    // Parameters: int, int
    int (*fcnPtr2a)(int, int){ randFunct2 };
    int x = 1, y = 2;
    fcnPtr2a(x, y);

    std::cout << "-------------------------\n";

    // 2)
    std::function<int(int, int)> fcnPtr2b{ randFunct2 };
    fcnPtr2b(3, 4);

    std::cout << "-------------------------\n";

    // Initialize it with other function pointer
    std::function<int(int, int)> fcnPtr2c{ fcnPtr2b };
    fcnPtr2c(5, 6);

    std::cout << "-------------------------\n";

    // 3)
    auto fcnPtr3{ randFunct3 };
    fcnPtr3("HelloWorld!");

    std::cout << "-------------------------\n";

    /*
     * Assignments
     */
    std::function<int(int, int)> fcnPtr4a{ randFunct4 };
    std::function<int(int, int)> fcnPtr4b;
    fcnPtr4b = fcnPtr4a;
    fcnPtr4b(7, 8);

    std::cout << "-------------------------\n";

    // using alias for function pointer
    using fnctPtrAssig = int(*)(int, int);
    fnctPtrAssig fcnPtr4c{ randFunct4 };
    fcnPtr4c(9, 10);

    std::cout << "*****************************************************\n";
    return 0;
}