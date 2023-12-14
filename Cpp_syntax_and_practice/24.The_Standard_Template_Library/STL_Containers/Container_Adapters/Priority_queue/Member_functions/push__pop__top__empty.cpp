#include <iostream>
#include <queue>
#include <vector>

//* Printing priority_queue
// - priority_queue, since it is implemented as vector and we are using 'top()' function,
//   will print elements in opposite direction from inserting elements
template <typename T>
void printPrioQueue(T& varPrioQue)
{
    int i = 1;
    while(!varPrioQue.empty())
    {
        std::cout << varPrioQue.top() << " (" << i << ". element popped) \n";
        varPrioQue.pop();
        ++i;
    }
}

int main()
{
    std::cout << "*****************************************************\n";

    //* Define priority queue sorted in ascending order (default)
    // - internally implemented as max heap
    std::priority_queue<int> varPrioQue1;
    for(int elem : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
    {
        varPrioQue1.push(elem);
    }
    printPrioQueue(varPrioQue1);

    std::cout << "--------------------------------------------\n";
    //////////////////////////////////////////////////////////////////////
    
    //* Define priority queue sorted in descending order
    // - internally implemented as min heap
    std::priority_queue< int, std::vector<int>, std::greater<int> > varPrioQue2;
    for(int elem : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
    {
        varPrioQue2.push(elem);
    }
    printPrioQueue(varPrioQue2);

    std::cout << "--------------------------------------------\n";
    //////////////////////////////////////////////////////////////////////

    //* Define priority queue sorted in ascending order using lambda function
    auto cmp = [](int left, int right) { return (left) < (right); };
    std::priority_queue< int, std::vector<int>, decltype(cmp) > varPrioQue3(cmp);
    for(int elem : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
    {
        varPrioQue3.push(elem);
    }
    printPrioQueue(varPrioQue3);

    std::cout << "*****************************************************\n";
    return 0;
}