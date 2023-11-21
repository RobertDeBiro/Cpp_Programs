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

    int n;
    std::cout << "Insert integer: ";
    std::cin >> n;

    char flag;
    std::cout << "Print assert message(y/n)?\n";
    std::cin >> flag;

    //********** Assert with description **********
    // - if n is not a prime, program execution will be aborted and
    //   exception will be called
    assert(isPrime(n) && "ERROR: Number is not prime!");

    // ********** Assert **********
    if(flag == 'n')
        assert(isPrime(n));
    else
        assert(isPrime(n) && "ERROR: Number is not prime!");

    std::cout << "*****************************************************\n";
    return 0;
}
