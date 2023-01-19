#include <iostream>

void top_level_const();
void low_level_const();

int main()
{
    std::cout << "*****************************************************\n";

    top_level_const();
    low_level_const();

    std::cout << "*****************************************************\n";
    return 0;
}

void top_level_const()
{
    int var1 = 1;
    int var2 = 2;
    int *const ptr1{ &var1 };
    // We cannot change value of the pointer
    //ptr1 = &var2;
    std::cout << "*ptr1 = " << *ptr1 << '\n';

    /*
     * Copy of top-level pointer
     *  - when copy top-level const pointers, consts are ignored
     *  - the pointer to which we copy doesn't depend on the const status of the coppied pointer
     *    - hence, the pointer to which we copy can, or doesn't have to, be const, no matter what
     */
    int* ptr2a{ &var1 };
    int *const ptr2b{ &var2 };
    const int* ptr3a = ptr2a;
    int* ptr3b = ptr2b;
    std::cout << "*ptr3a = " << *ptr3a << '\n';
    std::cout << "*ptr3b = " << *ptr3b << '\n';

    std::cout << "------------------------------\n";
}

void low_level_const()
{
    int var1 = 1;
    const int* ptr1a{ &var1 };
    // We cannot change value of the variable pointed by pointer
    // *ptr1b = 2;
    std::cout << "*ptr1a = " << *ptr1a << '\n';

    const int var2 = 2;
    const int* ptr2a{ &var2 };
    // const variable can be pointed only by "pointer to const"
    // int* ptr2b{ &var2 };
    std::cout << "*ptr2a = " << *ptr2a << '\n';

    /*
     * Copy of low-level pointer
     *  - when copy low-level const pointers, consts are NOT ignored
     *  - if pointer that is coppied contains low-level const
     *      - the pointer to which we copy also needs to contain low-level const
     *  - if pointer that is coppied doesn't contain low-level const
     *      - the pointer to which we copy can, or doesn't have to, contain low-level const
     */
    const int* ptr3a = ptr1a;
    //int* ptr3b = ptr1a;
    std::cout << "*ptr3a = " << *ptr3a << '\n';

    std::cout << "------------------------------\n";
}
