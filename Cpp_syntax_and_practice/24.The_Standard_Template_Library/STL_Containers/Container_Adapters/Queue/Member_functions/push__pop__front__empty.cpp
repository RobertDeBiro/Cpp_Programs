#include <iostream>
#include <queue>

//* Printing queue
//  - printing queue is specific since we can access only the 'first' element
//  - therefore, after printing that first we can access, we need to 'pop' it out
//  - elements are popped out in the opposite direction from 'std::stack'
void printQueue(std::queue<int> varQue)
{
    int i = 1;
    while(!varQue.empty())
    {
        std::cout << varQue.front() << " (" << i << ". element popped) \n";
        varQue.pop();
        ++i;
    }
}

int main()
{
    std::cout << "*****************************************************\n";

    std::queue<int> varQue;
    varQue.push(1);
    varQue.push(2);
    varQue.push(3);
    std::cout << "Printing queue: \n";
    printQueue(varQue);

    std::cout << "*****************************************************\n";
    return 0;
}
