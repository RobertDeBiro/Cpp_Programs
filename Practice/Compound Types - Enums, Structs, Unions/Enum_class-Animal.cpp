// Scoped enumerations (enum classes)

#include <iostream>
#include <string_view>

enum class Animal
{
    pig,
    chicken,
    goat,
    cat,
    dog,
    duck,
};

constexpr std::string_view getAnimalName(Animal animal)
{
    switch(animal)
    {
        case Animal::pig:       return "pig";
        case Animal::chicken:   return "chicken";
        case Animal::goat:      return "goat";
        case Animal::cat:       return "cat";
        case Animal::dog:       return "dog";
        case Animal::duck:      return "duck";
        default:                return "???";
    }
}

void printNumberOfLegs(Animal animal)
{
    // Here we can see switch fallthrough
    // - in order to avoid possible warnings by the compiler we can use [[fallthrough]] attribute (from C++17)
    switch(animal)
    {
        case Animal::pig:
        case Animal::goat:
        case Animal::cat:
        case Animal::dog:
            std::cout << "A " << getAnimalName(animal) << " has 4 legs." << '\n';
            break;
        case Animal::chicken:
        case Animal::duck:
            std::cout << "A " << getAnimalName(animal) << " has 2 legs." << '\n';
            break;
        default:
            std::cout << "There is no such animal!" << '\n';
            break;
    }
}

int main()
{
    printNumberOfLegs(Animal::cat);
    printNumberOfLegs(Animal::chicken);

    return 0;
}
