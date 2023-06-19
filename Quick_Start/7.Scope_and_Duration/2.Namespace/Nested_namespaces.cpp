#include <iostream>

void printDivMsg()
{
    std::cout << "Divide!\n";
}

namespace outer
{
    void printMultMsg()
    {
        std::cout << "Multiply!\n";
    }

    namespace inner // inner is a namespace inside the outer namespace
    {
        void printAddMsg()
        {
            std::cout << "Addition!\n";
        }

        int add(int x, int y)
        {
            printAddMsg();
            return x + y;
        }

        int multiply(int x, int y)
        {
            printMultMsg();
            return x + y;
        }
        
        int divide(int x, int y)
        {
            printDivMsg();
            return x / y;
        }
    }
}

int main()
{
    std::cout << outer::inner::add(2, 3) << '\n';
    std::cout << outer::inner::multiply(2, 3) << '\n';
    std::cout << outer::inner::divide(2, 3) << '\n';

    // Namespace alias
    namespace outin = outer::inner;

    std::cout << outin::add(2, 3) << '\n';
    std::cout << outin::multiply(2, 3) << '\n';
    std::cout << outin::divide(2, 3) << '\n';

    return 0;
}