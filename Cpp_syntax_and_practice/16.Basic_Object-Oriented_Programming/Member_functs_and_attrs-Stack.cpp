/*
 * LearnCpp
 * Basic Object-oriented Programming
 * Public vs private access specifiers
 */

#include <iostream>
#include <cassert>
#include <iterator>

class Stack
{
    int arr[10]{};
    int m_size{};

public:
    void reset()
    {
        m_size = 0;
    }

    bool push(int x)
    {
        if(m_size == static_cast<int>(std::size(arr)))
            return false;

        arr[m_size++] = x;
        return true; // We are returning booleans true or false, but we are not using that information
    }

    // When talking about stack behavior, pop function does two things:
    //  1. Removes element from the stack (not covered in following function)
    //  2. Returns back popped element (covered in following function)
    int pop()
    {
        assert(m_size > 0  && "Can not pop empty stack");
        return arr[--m_size]; // We are returning the poped element, but we are not using that information
    }

    void print()
    {
        std::cout << "( ";
        for(int i = 0; i < m_size; i++)
            std::cout << arr[i] << ' ';
        std::cout << ")\n";
    }
};

int main()
{
    std::cout << "*****************************************************\n";

	Stack stack;
	stack.reset();

	stack.print();

	stack.push(5);
	stack.push(3);
	stack.push(8);
	stack.print();

	stack.pop();
	stack.print();

	stack.pop();
	stack.pop();

	stack.print();

    std::cout << "*****************************************************\n";
	return 0;
}
