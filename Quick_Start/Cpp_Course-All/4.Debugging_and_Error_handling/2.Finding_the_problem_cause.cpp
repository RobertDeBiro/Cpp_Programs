/**
 * * Finding the root cause of the problem
 *      - commenting out the code
 *      - validate the code flow
 *      - print values
 **/

#include <iostream>

void funct1()
{
    std::cerr << "**** 1 *****" << std::endl;
    std::cout << "Name: John Smith!" << std::endl;
}

void funct2()
{
    std::cerr << "**** 2 *****" << std::endl;
    std::cout << "Height: 190 cm" << std::endl;
}

void funct3()
{
    std::cerr << "**** 3 *****" << std::endl;
    std::cout << "*?(!@)=(*" << std::endl;
}

void funct4()
{
    std::cerr << "**** 4 *****" << std::endl;
    std::cout << "Address: 4542 Saint James Drive" << std::endl;
}

void funct5(int year)
{
    std::cerr << "year in funct5 = " << year << std::endl;
    std::cout << year << " years old" << std::endl;
}

int main()
{
    std::cout << "Print user data:" << std::endl;
    funct1();
    funct2();
    funct3();
    funct4();

    int Year = 55;
    int year;
    std::cout << "Insert years: ";
    std::cin >> year;
    std::cerr << "year in main = " << year << std::endl;
    funct5(Year);

    return 0;
}