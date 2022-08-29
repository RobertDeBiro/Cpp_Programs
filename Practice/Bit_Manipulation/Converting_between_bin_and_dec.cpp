#include <iostream>

unsigned int getNumber()
{
    std::cout << "Enter number between 0 and 255: ";
    unsigned int x{};
    std::cin >> x;

    return x;
}

unsigned int printBitReturnVal(unsigned int decNumber, unsigned int digitVal)
{
    if (decNumber >= digitVal)
    {
        std::cout << 1;
        return (decNumber - digitVal);
    }
    else
    {
        std::cout << 0;
        return decNumber;
    }
}

int main()
{
    unsigned int decNumber{ getNumber() };

    decNumber = printBitReturnVal(decNumber, 128);
    decNumber = printBitReturnVal(decNumber, 64);
    decNumber = printBitReturnVal(decNumber, 32);
    decNumber = printBitReturnVal(decNumber, 16);
    std::cout << ' ';
    decNumber = printBitReturnVal(decNumber, 8);
    decNumber = printBitReturnVal(decNumber, 4);
    decNumber = printBitReturnVal(decNumber, 2);
    decNumber = printBitReturnVal(decNumber, 1);

    return 0;
}
