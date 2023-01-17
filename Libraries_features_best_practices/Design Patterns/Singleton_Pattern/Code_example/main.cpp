#include <iostream>
#include "Singleton.hpp"

void printInstanceStatus(Singleton* instance)
{
    if(instance)
        std::cout << "Singleton instance fetched! Instance address: " << instance << std::endl;
    else
        std::cout << "ERROR: Singleton instance NOT fetched!" << std::endl;
}

int main()
{
    std::cout << "\n********** Singleton pattern! **********\n" << std::endl;

    Singleton* instance = Singleton::getInstance();
    printInstanceStatus(instance);

    std::cout << '\n';

    Singleton* instance2 = Singleton::getInstance();
    printInstanceStatus(instance2);

    return 0;
}