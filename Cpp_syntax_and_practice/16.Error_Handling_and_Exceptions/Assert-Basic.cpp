#include <iostream>
#include <cassert>

bool isPrime(int x)
{
    if (x == 0 || x == 1)
        return false;

    for(int div{ x/2 }; div >= 1; --div)
    {
        if((div != 1) && (x % div == 0))
            return false;
    }

    return true;
}

int main()
{
    std::cout << "*****************************************************\n";

    char flag;
    std::cout << "Print assert message(y/n)?\n";
    std::cin >> flag;

    assert(isPrime(2) && "ERROR: Number is not prime!");

    if(flag == 'n')
        assert(isPrime(4));
    else
        assert(isPrime(6) && "ERROR: Number is not prime!");

    std::cout << "*****************************************************\n";
    return 0;
}
