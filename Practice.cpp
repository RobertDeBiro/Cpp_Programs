#include <iostream>
#include <fstream>

int main()
{
    std::ofstream file{ "..." };

    if("file")
    {
        // ERROR
    }

    file << "Line1\n";

    return 0;
}