/*
 * Raw pointer
 *
 *  - bad:
 *      - memory leak - pointer not deleted
 */

#include <iostream>

class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
    void sayHi() { std::cout << "Hi!\n"; }
};

void someFunction()
{
    Resource *ptr = new Resource();

    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if (x == 0)
        return; // the function returns early, and 'ptr' won’t be deleted - memory leak happens!

    // do stuff with 'ptr' here
    ptr->sayHi();

    delete ptr;
}

int main()
{
    std::cout << "*****************************************************\n";

    someFunction();

    std::cout << "*****************************************************\n";
    return 0;
}