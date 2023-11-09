/*
 * LearnCpp
 * Control Flow
 * Intro to loops and while statements
 */

#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

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

    std::cout << "*****************************************************\n";
    return 0;
}
