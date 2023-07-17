//* Pointers and const
/**
 *  Pointer to a const value:
 *?     const int* ptr = &a;
 *   
 *  Const pointer:
 *?     int* const ptr = &a
 *
 *  Const pointer to a const value
 *?     const int* const ptr = &a
 **/

#include <iostream>

int main()
{
    //* Pointer to a const value
    const int a = 5;
    //int* ptr1 = &a;        //! We cannot assign pointer to a const value
    const int* ptr1 = &a;    // Pointer to const value
    //(*ptr1) = 10;          //! We cannot change value of pointed const value

    // We can initialize "pointer to const value" even though value may not be const
    int b = 10;
    const int* ptr2 = &b;
    b = 20;
    //*ptr2 = 20;

    //////////////////////////////////////////////////////////////////

    //* Const pointer
    int c = 100;
    int d = 200;
    int* ptr3 = &c;
    ptr3 = &d;

    int* const ptr4 = &c;
    //ptr4 = &d; //! We cannot change const pointer

    //////////////////////////////////////////////////////////////////

    //* Const pointer to a const value
    const int e = 1000;
    const int* const ptr5 = &e;
    //*ptr5 = 10000;
    //ptr5 = &a;

    return 0;
}