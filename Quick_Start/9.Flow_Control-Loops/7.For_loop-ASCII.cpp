#include <iostream>

int main()
{
    // If one statement, blocks not mandatory (counts also for while loop)
    for(char letter = 'a'; letter <= 'z'; letter++)
        std::cout << letter << " = " << static_cast<int>(letter) << '\n';

    return 0;
}