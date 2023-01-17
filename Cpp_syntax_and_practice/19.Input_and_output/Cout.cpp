#include <iostream>

int main()
{
    int a = 5;
    int b = 4;
    int c = 2;
    std::cout << c * (a + b) << std::endl;
    std::cout << (0==0) << std::endl;
    std::cout << ("0==0") << std::endl; // Parenthesis only serve for precedence in evaluation -
                                        // std::cout prints as a string only between quotes
    std::cout << "(0==0)" << std::endl;

    return 0;
}
