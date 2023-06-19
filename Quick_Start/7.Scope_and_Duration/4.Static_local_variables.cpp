//* Static local variable
/**
 *  - static duration
 *  - common to use "s_" as a variable name prefix
 *  - initialization is only done once, during compilation
 *      - zero initialized by defualt, just like other objects with static duration
 *  - common use for unique ID generators
 **/

#include <iostream>

void sayHello()
{
    static int s_user = 0;
    ++s_user;

    std::cout << "Hello from user " << s_user << '\n';
}

int main()
{
    sayHello();
    sayHello();
    sayHello();
    sayHello();

	return 0;
}
