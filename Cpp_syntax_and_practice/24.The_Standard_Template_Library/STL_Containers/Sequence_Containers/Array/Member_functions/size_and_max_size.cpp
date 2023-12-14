#include <iostream>
#include <array>

int main()
{
    std::cout << "*****************************************************\n";

    std::array<int, 150230> varArr;

    //* Get array size
    std::cout << "varArr size: " << varArr.size() << '\n';

    //* Get possible maximum array size
    //  - returns maximum number of elements the container is able to hold due to system or
    //    library implementation limitations
    std::cout << "varArr max_size: " << varArr.max_size() << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
