#include <iostream>
#include <iterator>

void funct1a(int *arr, size_t arr_size)
{
    std::cout << "funct1a, 1. Array: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << *(arr + i) << ' ';
    
    std::cout << '\n';
    *(arr) = 2;

    std::cout << "funct1a, 2. Array: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << *(arr + i) << ' ';
    
    std::cout << '\n';
}

void funct1b(int **arr, size_t arr_size)
{
    std::cout << "funct1b, 1. Array: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << **(arr + i) << ' ';
    
    std::cout << '\n';
    **(arr) = 2;

    std::cout << "funct1b, 2. Array: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << **(arr + i) << ' ';
    
    std::cout << '\n';
}

void funct2a(const int *arr, size_t arr_size)
{
    std::cout << "funct2, 1. Array: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << *(arr + i) << ' ';
    
    std::cout << '\n';

    // Following part fails because we cannot change pointer to const!
    // *(arr) = 2;
}

void funct2b(const int **arr, size_t arr_size)
{
    std::cout << "funct2, 1. Array: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << **(arr + i) << ' ';
    
    std::cout << '\n';

    // Following part fails because we cannot change pointer to const!
    // *(arr) = 2;
}

void funct2c(const int **const arr, size_t arr_size)
{
    std::cout << "funct2, 1. Array: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << **(arr + i) << ' ';
    
    std::cout << '\n';

    // Following part fails because we cannot change pointer to const!
    // *(arr) = 2;
}

void funct2d(const int *const *const arr, size_t arr_size)
{
    std::cout << "funct2, 1. Array: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << **(arr + i) << ' ';
    
    std::cout << '\n';

    // Following part fails because we cannot change pointer to const!
    // *(arr) = 2;
}

int main()
{
    std::cout << "*****************************************************\n";

    int elem1 = 1, elem2 = 2, elem3 = 3;

    int arr1a[3]{ elem1, elem2, elem3 };
    size_t arr1a_size{ std::size(arr1a) };
    funct1a(arr1a, arr1a_size);

    int* arr1b[3]{ &elem1, &elem2, &elem3 };
    size_t arr1b_size{ std::size(arr1b) };
    funct1b(arr1b, arr1b_size);

    const int arr2a[3]{ elem1, elem2, elem3 };
    size_t arr2a_size{ std::size(arr2a) };
    funct2a(arr2a, arr2a_size);

    const int* arr2b[3]{ &elem1, &elem2, &elem3 };
    size_t arr2b_size{ std::size(arr2b) };
    funct2b(arr2b, arr2b_size);
    funct2c(arr2b, arr2b_size);
    funct2d(arr2b, arr2b_size);

    std::cout << "*****************************************************\n";

    return 0;
}