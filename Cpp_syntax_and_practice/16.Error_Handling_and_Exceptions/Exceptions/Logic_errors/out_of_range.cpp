#include <iostream>
#include <vector>
#include <stdexcept> // std::out_of_range

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> v;
    v.push_back(1);
    try
    {
        int j = v.at(99);
        std::cout << "j = " << j << std::endl;
    }
    catch(std::out_of_range& e)
    {
        std::cout << "out of range exception " << e.what() << '\n';
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    std::cout << "*****************************************************\n";
    return 0;
}
