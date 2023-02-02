#include <iostream>
#include <tuple> // std::tuple, std::tie

std::tuple<int, int> initialUserInput()
{
    std::cout << "Start where? ";
    int x;
    std::cin >> x;

    std::cout << "How many? ";
    int y;
    std::cin >> y;
    
    std::tuple<int, int> inituser{ x, y };  return inituser;
}

int main()
{
    std::cout << "*****************************************************\n";

    /*
    * Create tuple
    */
    std::cout << "Enter first tuple element: ";
    int x;
    std::cin >> x;

    std::cout << "Enter second tuple element: ";
    int y;
    std::cin >> y;
    
    std::tuple<int, int> varTuple{ x, y };
    std::cout << "Entered touple: {" << std::get<0>(varTuple) << ", "
              << std::get<1>(varTuple) << "}\n";

    /*
    * Unpack tuple
    */
    int k, z;
    std::tie(k, z) = varTuple;
    std::cout << "Unpacked tuple: " << k << " " << z << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
