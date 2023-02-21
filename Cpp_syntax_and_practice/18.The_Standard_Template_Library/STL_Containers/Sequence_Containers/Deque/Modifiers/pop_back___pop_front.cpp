#include <iostream>
#include <deque>

void printDeque(const std::deque<int>& varDeq)
{
    for(int elem : varDeq)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::deque<int> varDeq { 1, 2, 3, 4, 5 };
    std::cout << "Initial deque: ";
    printDeque(varDeq);

    varDeq.pop_front();
    varDeq.pop_back();
    std::cout << "Deque after popping elements at front and back: ";
    printDeque(varDeq);

    std::cout << "*****************************************************\n";
    return 0;
}
