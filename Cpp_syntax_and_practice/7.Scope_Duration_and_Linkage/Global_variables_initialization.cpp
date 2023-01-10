#include <iostream>

int g_i;

int main()
{
    int local_i;
    
    // Local variable is uninitialized when declaring it
    //  - we will obtain compiler warning that local_i is uninitialized
    //  - behavior(value) is undefined
    std::cout << "local_i = " << local_i << std::endl;
    
    // global variable is automatically initialized when declaring it
    std::cout << "g_i = " << g_i << std::endl;

    return 0;
}