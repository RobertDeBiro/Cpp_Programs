#include <iostream>

int main()
{
    int x = 5;
    int y = 0;
    int z = x / y; //! Run-time error (Exception error) - We cannot divide with 0

    std::cout << z << std::endl;
    
    return 0;
}