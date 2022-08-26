#include <iostream>
#include <vector>
//#include <exception> -> not necessary because it is included inside vector library

int main()
{
    std::vector<int> v;
    v.push_back(1);
    try
    {
        int j = v.at(99);
        std::cout << "j = " << j << std::endl;
    }
    catch(std::out_of_range& e)
    {
        std::cout << "\nout of range exception " << e.what();
    }
    catch(std::exception& e)
    {
        std::cout << '\n' << e.what();
    }
    return 0;
}
