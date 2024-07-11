#include <iostream>
#include <algorithm>

int main()
{
#ifdef CURRENT_TIME
    std::cout << "Release mode!" << std::endl;
    const char* current_time = CURRENT_TIME;
    std::cout << "Build time is: " << current_time << std::endl;
#else
    std::cout << "Debug mode - no current time shown!" << std::endl;
#endif

    return 0;
}