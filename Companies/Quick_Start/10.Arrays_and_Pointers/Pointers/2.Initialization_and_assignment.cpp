#include <iostream>

int main()
{
    int a = 10;
    int b = 20;
    double c = 30.0;

    //* Pointer initialization
    int* p1 = &a;       // Initialize with int object address
    double* p2 = &c;    // Initialize with double object address
    int* p3{};          // Zero initialization
    int* p4;            // No initialization, only declaration
    int* p5 = &a;       // We can have two pointers pointing to the same object

    std::cout << "p1 = " << p1 << "; *p1 = " << *p1 << '\n';
    std::cout << "p2 = " << p2 << "; *p2 = " << *p2 << '\n';

    //! ERROR - Segmentation fault!
    //! -> We cannot dereference zero-initialized pointer
    // std::cout << "p3 = " << p3 << "; *p3 = " << *p3 << '\n';
    std::cout << "p3 = " << p3 << '\n';

    //! ERROR - Segmentation fault!
    //! -> We cannot dereference zero-initialized pointer
    // std::cout << "p4 = " << p4 << "; *p4 = " << *p4 << '\n';
    // std::cout << "p4 = " << p4 << '\n';

    std::cout << "p5 = " << p5 << "; *p5 = " << *p5 << '\n';

    std::cout << "-------------------------------------------------------------\n";

    //* Pointer assignment
    p1 = &b;        // Assign pointer to another object address
    std::cout << "p1 = " << p1 << "; *p1 = " << *p1 << '\n';

    //! ERROR
    //! -> We cannot assign "pointer to int" to double
    // p1 = &c;

    ///////////////////////////////////////////////////////////////////////////////

    //* Dangling pointer
    int* p8{};
    {
        int d = 100;
        p8 = &d;
        std::cout << "p8 = " << p8 << "; *p8 = " << *p8 << '\n';
    } // d is destroyed here
    // Dangling pointer - pointer points to non-existing object (to free memory)
    std::cout << "p8 = " << p8 << "; *p8 = " << *p8 << '\n';

    p8 = nullptr;
    if(p8 != nullptr)
        std::cout << "p8 = " << p8 << "; *p8 = " << *p8 << '\n';
    else
        std::cout << "p8 doesn't point to any address!\n";

    return 0;
}