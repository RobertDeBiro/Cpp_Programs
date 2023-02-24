#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    int n = 5;
    /*
    while(--n):
     - first "n" is decremented, and then evaluated, and then "while" is evaluated on evaluated n
     - means that following loop will have 4 iterations:
        - "n" will be evaluated as following: 4, 3, 2, 1

    while(n--)
     - first "n" is evaluated and then decremented, and then "while" is evaluated on evaluated n
     - means that following loop will have 5 iterations:
        - "n" will be evaluated as following: 4, 3, 2, 1, 0
        - in first iteration while reads n = 5
    */

    //while(--n)
    while(n--)
    {
        std::cout << n << std::endl;
    }
    
    std::cout << "*****************************************************\n";
    return 0;
}
