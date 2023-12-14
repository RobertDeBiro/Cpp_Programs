#include <iostream>
#include <stack>
#include <vector>

//* Printing stack
//  - printing stack is specific since we can access only the 'top' element
//  - therefore, after printing that 'top' element that we can access, we need to 'pop' it out
//  - elements are popped out in the opposite direction from 'std::queue'
void printStack(std::stack<int> varStk)
{
    int i = 1;
    while(!varStk.empty())
    {
        std::cout << varStk.top() << " (" << i << ". element popped) \n";
        varStk.pop();
        ++i;
    }
}

void printStack(std::stack<int, std::vector<int>> varStk)
{
    int i = 1;
    while(!varStk.empty())
    {
        std::cout << varStk.top() << " (" << i << ". element popped) \n";
        varStk.pop();
        ++i;
    }
}

int main()
{
    std::cout << "*****************************************************\n";

    //* 'std::stack' with 'std::deque' as internal container (default)
    std::stack<int> varStk1;
    varStk1.push(1);
    varStk1.push(2);
    varStk1.push(3);
    std::cout << "Printing stack with deque: \n";
    printStack(varStk1);

    std::cout << "----------------------------\n";

    //* 'std::stack' with 'std::vector' as internal container
    //  - if using 'std::vector' as an internal container, rather then 'std::deque',
    //    printout will be the same, but internal managament of the stack is not the same
    std::stack<int, std::vector<int>> varStk2;
    varStk2.push(1);
    varStk2.push(2);
    varStk2.push(3);
    std::cout << "Printing stack with vector: \n";
    printStack(varStk2);

    ///////////////////////////////////////////////////////////

    // It is not possible to initialize stack by using initializer list, must be initialized with 'push()'
    //! std::stack<int> varStk3{ 1, 2, 3 };

    std::cout << "*****************************************************\n";
    return 0;
}
