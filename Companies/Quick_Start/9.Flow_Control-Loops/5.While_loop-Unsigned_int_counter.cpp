#include <iostream>

int main()
{
    unsigned int count{ 10 }; // note: unsigned

    while (count >= 0)
    {
        if (count == 0)
        {
            std::cout << "Go out!";
        }
        else
        {
            std::cout << count << ' ';
        }
        --count;
    }

    return 0;
}