// LearnCpp
// Arrays, Strings, and Dynamic Allocation
// Arrays (Part II)

#include <iostream>

namespace Creatures
{
    enum Animals
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        number_of_animals
    };
}


int main()
{
    std::cout << "*****************************************************\n";

    // Defining size of the array inside brackets[], which is not mandatory since we initialized array
    int animalLegs[Creatures::number_of_animals] {2, 4, 4, 4, 2, 0};

    std::cout << "Elephant has " << animalLegs[Creatures::elephant] << " legs." << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
