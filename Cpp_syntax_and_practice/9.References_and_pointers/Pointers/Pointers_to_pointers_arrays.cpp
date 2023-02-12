#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    int arr1[3]{ 1, 2, 3 };
    int arr2[3]{ 2, 3, 4 };
    int arr3[3]{ 3, 4, 5 };

    // Set array with arrays using operator[]
    int* arrArr1[3]{ arr1, arr2, arr3 };
    std::cout << *arrArr1[0] << ' ' << *(arrArr1[0] + 1) << ' ' << *(arrArr1[0] + 2) << '\n';
    std::cout << *arrArr1[1] << ' ' << *(arrArr1[1] + 1) << ' ' << *(arrArr1[1] + 2) << '\n';
    std::cout << *arrArr1[2] << ' ' << *(arrArr1[2] + 1) << ' ' << *(arrArr1[2] + 2) << '\n';

    std::cout << "------------------------------------\n";

    // Set array with arrays using *
    //  - it is not possible to initialize array in follwoing way
    int** arrArr2{ arrArr1 };
    std::cout << **arrArr2 << ' ' << *(*arrArr2 + 1) << ' ' << *(*arrArr2 + 2) << '\n';
    std::cout << **(arrArr2 + 1) << ' ' << *(*(arrArr2 + 1) + 1) << ' ' << *(*(arrArr2 + 1) + 2) << '\n';
    std::cout << **(arrArr2 + 2) << ' ' << *(*(arrArr2 + 2) + 1) << ' ' << *(*(arrArr2 + 2) + 2) << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}