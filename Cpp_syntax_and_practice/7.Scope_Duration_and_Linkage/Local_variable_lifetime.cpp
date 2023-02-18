// LearncCpp
// Object_Scope_and_Conversions
// Local variables

#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    std::cout << "Enter an integer: ";
    int smaller{}; // Variable smaller is created here - its lifetime begins
    std::cin >> smaller;

    std::cout << "Enter a larger integer: ";
    int larger{}; // Variable larger is created here - its lifetime begins
    std::cin >> larger;

    if(smaller > larger)
    {
        std::cout << "Swapping the values.\n";
        int temp{ larger }; // Variable temp is created here - its lifetime begins
        larger = smaller;
        smaller = temp;
    } // Variable temp dies here - it's lifetime ends

    std::cout << "The smaller value is " << smaller << "\n";
    std::cout << "The larger value is " << larger << "\n";

    std::cout << "*****************************************************\n";
    return 0;
} // Variables smaller and larger die here - their lifetime ends
