// LearnCpp
// 7. Control Flow and Error Handling
// Intro to loops and while statements

#include <iostream>

int main()
{
    int outer{ 5 };
    while(outer >= 1)
    {
        int inner{ outer };
        while(inner >= 1)
        {
            std::cout << inner << ' ';
            --inner;
        }
        --outer;
        std::cout << '\n';
    }

    std::cout << "--------------------\n";

    outer = 1;
    while(outer <= 5)
    {
        int inner{ 5 };
        while(inner > 0)
        {
            if(inner <= outer)
                std::cout << inner;
            else
                std::cout << " ";
            std::cout << " ";
            --inner;
        }
        std::cout << '\n';
        ++outer;
    }

    return 0;
}
