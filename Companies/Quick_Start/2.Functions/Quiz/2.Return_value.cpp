// Determine what the programs will output, or whether the programs will generate a compiler error

#include <iostream>

// 1)
// int return1()
// {
//     return 1;
// }

// int return2()
// {
//     return 2;
// }

// int main()
// {
//     std::cout << return1() + return2() << std::endl;

//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////

// 2)
// int return1()
// {
//     return 1;

//     int return2()
//     {
//         return 2;
//     }
// }

// int main()
// {
//     std::cout << return1() + return2() << std::endl;

//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////

// 3)
// int return1()
// {
//     return 1;
// }

// int return2()
// {
//     return 2;
// }

// int main()
// {
//     return1();
//     return2();

//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////

// 4)
// int getNum()
// {
//     return 1;
//     return 2;
// }

// int main()
// {
//     std::cout << getNum() << std::endl;
//     std::cout << getNum() << std::endl;

//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////

// 5)
void printA()
{
    std::cout << "A" << std::endl;
}

void printB()
{
    std::cout << "B" << std::endl;
}

int main()
{
    printA();
    std::cout << printB() << std::endl;

    return 0;
}