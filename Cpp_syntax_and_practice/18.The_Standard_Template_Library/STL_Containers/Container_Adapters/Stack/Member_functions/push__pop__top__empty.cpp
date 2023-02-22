/*
 * push( const value_type& value ) -> void
 *
 * pop() -> void
 * 
 * top() -> reference
 * 
 * empty() const -> bool
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/container/stack/push
 *  - https://en.cppreference.com/w/cpp/container/stack/pop
 *  - https://en.cppreference.com/w/cpp/container/stack/top
 *  - https://en.cppreference.com/w/cpp/container/stack/empty
 */

#include <iostream>
#include <stack>
#include <vector>

// Printing stack is specific since we can access only the top element
//  - therefore, after printing that top element that we can access, we need to pop it out
//  - elements are popped out in the opposite direction from std::queue
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

    std::stack<int> varStk1;
    varStk1.push(1);
    varStk1.push(2);
    varStk1.push(3);
    std::cout << "Printing stack with deque: \n";
    printStack(varStk1);

    std::cout << "----------------------------\n";

    // If using std::vector as an internal container, rather then std::deque,
    // printout will be the same, but internal managament of the stack is not the same
    std::stack<int, std::vector<int>> varStk2;
    varStk2.push(1);
    varStk2.push(2);
    varStk2.push(3);
    std::cout << "Printing stack with vector: \n";
    printStack(varStk2);

    std::cout << "*****************************************************\n";
    return 0;
}
