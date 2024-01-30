//* Static local variable
/**
 *  - static duration
 *  - common to use "s_" as a variable name prefix
 *  - initialization is only done once, during compilation
 *      - zero initialized by default, just like other objects with static duration
 *  - common use for unique ID generators
 **/

#include <iostream>

int generateId()
{
    static int s_id;
    ++s_id;

    return s_id;
}

int main()
{
    int u1 = generateId();
    std::cout << "User ID: " << u1 << '\n';

    int u2 = generateId();
    std::cout << "User ID: " << u2 << '\n';

    int u3 = generateId();
    std::cout << "User ID: " << u3 << '\n';

    int u4 = generateId();
    std::cout << "User ID: " << u4 << '\n';

	return 0;
}
