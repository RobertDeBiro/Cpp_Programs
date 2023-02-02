#include <iostream>
#include <iterator>

// "Array" containing "integers"
void f_arr_int(int *arr, size_t arr_size)
{
    std::cout << "1. Array of int: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << *(arr + i) << ' ';
    std::cout << '\n';

    // Array element can be changed
    *(arr) = 2;

    std::cout << "2. Array of int: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << *(arr + i) << ' ';
    std::cout << '\n';

    // Following changes address of local arr, not the one created in main function
    //  - because pointer is sent to function by value
    int temp;
    arr = &temp;
    std::cout << "3. Array of int (changed array address): \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << *(arr + i) << ' ';

    std::cout << "\n";
}

// "Array" containing "pointers to integers"
void f_arr_ptr(int **arr, size_t arr_size)
{
    std::cout << "1. Array of int*: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << **(arr + i) << ' ';
    std::cout << '\n';

    // Array element can be changed
    **(arr) = 2;

    std::cout << "2. Array of int*: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << **(arr + i) << ' ';

    std::cout << "\n-------------------------------\n";
}

// "Array" containing "const integers"
void f_arr_const_int(const int *arr, size_t arr_size)
{
    std::cout << "1. Array of const int: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << *(arr + i) << ' ';
    
    std::cout << "\n-------------------------------\n";

    // We cannot change element pointed by "pointer to const"
    // *(arr) = 2;
}

// "Array" containing "pointers to const integers"
void f_arr_ptr_const_int(const int **arr, size_t arr_size)
{
    std::cout << "1. Array of const int*: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << **(arr + i) << ' ';

    std::cout << "\n-------------------------------\n";

    // We cannot change element pointed by "pointer to const"
    //  - const in front of the data type is always pointer to const value, not const pointer
    //  - this makes sense because const pointer syntax is *const
    // **(arr) = 2;
}

// "Const array" containing "pointers to const integers"
void f_const_arr_ptr_const_int(const int **const arr, size_t arr_size)
{
    std::cout << "1. Array const int **const: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << **(arr + i) << ' ';
    
    std::cout << "\n-------------------------------\n";

    // Following part fails because we cannot change pointer to const!
    // *(arr) = 2;
}

// "Const array" containing "const pointers to const integers"
void f_const_arr_const_ptr_const_int(const int *const *const arr, size_t arr_size)
{
    std::cout << "1. Array const int *const *const: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << **(arr + i) << ' ';
    
    std::cout << "\n-------------------------------\n";

    // Following part fails because we cannot change pointer to const!
    // *(arr) = 2;
}

int main()
{
    std::cout << "*****************************************************\n";

    int elem1 = 1, elem2 = 2, elem3 = 3;

    int arr1a[3]{ elem1, elem2, elem3 };
    size_t arr1a_size{ std::size(arr1a) };
    f_arr_int(arr1a, arr1a_size);
    std::cout << "1. Array of int, in main: \n";
    for(int i = 0; i < static_cast<int>(arr1a_size); i++)
        std::cout << *(arr1a + i) << ' ';
    std::cout << "\n-------------------------------\n";

    int* arr1b[3]{ &elem1, &elem2, &elem3 };
    size_t arr1b_size{ std::size(arr1b) };
    f_arr_ptr(arr1b, arr1b_size);

    const int arr2a[3]{ elem1, elem2, elem3 };
    size_t arr2a_size{ std::size(arr2a) };
    f_arr_const_int(arr2a, arr2a_size);

    const int* arr2b[3]{ &elem1, &elem2, &elem3 };
    size_t arr2b_size{ std::size(arr2b) };
    f_arr_ptr_const_int(arr2b, arr2b_size);
    f_const_arr_ptr_const_int(arr2b, arr2b_size);
    f_const_arr_const_ptr_const_int(arr2b, arr2b_size);

    std::cout << "*****************************************************\n";
    return 0;
}