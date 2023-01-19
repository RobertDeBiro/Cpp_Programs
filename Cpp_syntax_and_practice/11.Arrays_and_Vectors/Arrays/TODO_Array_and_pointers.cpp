#include <iostream>
#include <iterator>

class ConstCl
{
    int m_x{};

public:
    ConstCl(int x = 0) : m_x{ x }
    {
        std::cout << "This is class for const!\n";
    }
};

void funct(const ConstCl *const *const arr)
{

}

void funct1(int *arr, size_t arr_size)
{
    std::cout << "funct1, 1. Array: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << *(arr + i) << ' ';
    
    std::cout << '\n';
    *(arr) = 2;

    std::cout << "funct1, 2. Array: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << *(arr + i) << ' ';
    
    std::cout << '\n';
}

void funct2(const int *arr, size_t arr_size)
{
    std::cout << "funct2, 1. Array: \n";
    for(int i = 0; i < static_cast<int>(arr_size); i++)
        std::cout << *(arr + i) << ' ';
    
    std::cout << '\n';

    // Following part fails because we cannot change pointer to const!
    // *(arr) = 2;
}

int main()
{
    std::cout << "*****************************************************\n";

    int arr1[3]{ 1, 2, 3 };
    size_t arr1_size{ std::size(arr1) };
    funct1(arr1, arr1_size);

    const int arr2[3]{ 1, 2, 3 };
    size_t arr2_size{ std::size(arr2) };
    funct2(arr2, arr2_size);

    const ConstCl constObj1;
    const ConstCl constObj2;
    const ConstCl constObj3;

    const ConstCl* arr[3] = {&constObj1, &constObj2, &constObj3};
    funct(arr);
    
    std::cout << "*****************************************************\n";

    return 0;
}