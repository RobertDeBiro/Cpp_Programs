#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    //********** Initialize arrays using operator[] **********
    int arr1[3]{ 1, 2, 3 };
    int arr2[3]{ 2, 3, 4 };
    int arr3[3]{ 3, 4, 5 };

    std::cout << arr1[0] << ' ' << arr1[1] << ' ' << arr1[2] << '\n';

    //********** Initialize array using operator* **********
    //  - when using operator* we can initialize array only with another array
    //! int* arrPtr2{ 7, 6, 5 };
    int* arrPtr1{ arr1 };

    std::cout << *arrPtr1 << ' ' << *(arrPtr1 + 1) << ' ' << *(arrPtr1 + 2) << '\n';

    std::cout << "------------------------------------\n";

    //********** Set array of arrays using operator[] **********
    int* arrArr1[3]{ arr1, arr2, arr3 };
    std::cout << *arrArr1[0] << ' ' << *(arrArr1[0] + 1) << ' ' << *(arrArr1[0] + 2) << '\n'; // print 'arr1' values
    std::cout << *arrArr1[1] << ' ' << *(arrArr1[1] + 1) << ' ' << *(arrArr1[1] + 2) << '\n'; // print 'arr2' values
    std::cout << *arrArr1[2] << ' ' << *(arrArr1[2] + 1) << ' ' << *(arrArr1[2] + 2) << '\n'; // print 'arr3' values

    std::cout << "------------------------------------\n";


    //********** Set array with arrays using operator* **********
    int** arrArr2{ arrArr1 };
    std::cout << **arrArr2 << ' ' << *(*arrArr2 + 1) << ' ' << *(*arrArr2 + 2) << '\n';                     // print 'arr1' values
    std::cout << **(arrArr2 + 1) << ' ' << *(*(arrArr2 + 1) + 1) << ' ' << *(*(arrArr2 + 1) + 2) << '\n';   // print 'arr2' values
    std::cout << **(arrArr2 + 2) << ' ' << *(*(arrArr2 + 2) + 1) << ' ' << *(*(arrArr2 + 2) + 2) << '\n';   // print 'arr3' values

    std::cout << "*****************************************************\n";
    return 0;
}