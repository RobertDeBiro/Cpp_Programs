#include <iostream>

//********** Global variable declaration **********
int g_i;

int main()
{
    std::cout << "*****************************************************\n";

    //********** Local variable declaration **********
    // - local variable is uninitialized when declared 
    // - we will obtain compiler warning that local_i is uninitialized
    // - behavior(value) is undefined
    int local_i;
    std::cout << "local_i = " << local_i << std::endl;

    // global variable is automatically initialized when declaring it
    std::cout << "g_i = " << g_i << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}