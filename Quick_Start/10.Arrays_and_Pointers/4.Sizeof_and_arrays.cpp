#include <iostream>
#include <iterator> // std::size()

int main()
{
    int arr[5] { 1, 2, 3, 4, 5 };

    //* Calculate array size (length) - prior to C++17
    // sizeof(arr) = number_of_elements x size_of_element"
    // sizeof(arr[0]) = size_of_element
    int size = sizeof(arr) / sizeof (arr[0]);
    std::cout << "Size of array is: " << size << '\n';

    //* Calculate array size (length)
    std::cout << "Size of array is: " << std::size(arr) << '\n';

    return 0;
}