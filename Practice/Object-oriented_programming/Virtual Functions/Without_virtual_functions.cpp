// LearncCpp - Pointers and references to the base class of derived objects

#include <iostream>
#include <string>
#include <array>

class Animal
{
protected:
    std::string m_name;
    std::string m_speak;

    // We're making this constructor protected because
    // we don't want people creating Animal objects directly,
    // but we still want derived classes to be able to use it.
    Animal(const std::string& name, const std::string& speak)
        : m_name{ name }, m_speak{ speak }
    {
    }

public:
    const std::string& getName() const { return m_name; }
    const std::string& speak() const { return m_speak; }
};

class Cat: public Animal
{
public:
    Cat(const std::string& name)
        : Animal{ name, "Meow" }
    {
    }
};

class Dog: public Animal
{
public:
    Dog(const std::string& name)
        : Animal{ name, "Woof" }
    {
    }
};

int main()
{
    const Cat fred{ "Fred" };
    const Cat misty{ "Misty" };
    const Cat zeke{ "Zeke" };

    const Dog garbo{ "Garbo" };
    const Dog pooky{ "Pooky" };
    const Dog truffle{ "Truffle" };

    // Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
    const std::array<const Animal*, 6> animals{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };
    for (const auto animal : animals)
        std::cout << animal->getName() << " says " << animal->speak() << '\n';

    return 0;
}
