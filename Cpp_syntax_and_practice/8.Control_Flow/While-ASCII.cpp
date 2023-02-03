// LearnCpp
// Control Flow and Error Handling
// Introduction to loops and while statements

#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";
    
    char letter{ 'a' };

    while(letter <= 'z')
    {
        std::cout << letter << " = " << static_cast<int>(letter) << '\n';
        ++letter; // char is actually uint8_t, hence it can be incremented with ++,
                  // but when printing with std::cout, it is printed as character
    }

    std::cout << "*****************************************************\n";
    return 0;
}
