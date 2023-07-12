#include <iostream>

int main()
{
    int outer{ 5 };
    int inner{};
    
    while(outer >= 1)
    {
        inner = outer;
        while(inner >= 1)
        {
            std::cout << inner << ' ';
            --inner;
        }
        --outer;
        std::cout << '\n';
    }

    return 0;
}
