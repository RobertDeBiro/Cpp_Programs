//* Structs
/**
 *  - a struct (short for structure) is a program-defined data type that allows us to bundle
 *    multiple variables and functions together into a single type
 *   - syntax:
 *?     struct Struct_Name
 *?     {
 *?         member_variable1,
 *?         member_variable2,
 *?         ...
 *?         member_variableN
 *?
 *?         member_function1,
 *?         member_function2,
 *?         ...
 *?         member_functionN,
 *?     };
 *  - variables that are part of the struct are called member variables
 *      - each variable has its own data type, and it is not required that they are equal
 *  - functions that are part of the struct are called member functions
 *  - definition must end with a semicolon
 *  - common to set name starting with a capital letter
 **/

#include <iostream>
#include <string>

enum StateOfBirth
{
    State_France,
    State_Nigeria,
    State_China,
    Unknown
};

// We can use default initialiation for our struct members
struct Animal
{
    std::string name{ "Beethoven" };
    std::string specie{ "Dog" };
    int age{ 5 };
    double weight_kg{ 20.2 };
};

void printAnimalInfo(const Animal& animal)
{
    std::cout << "Name: " << animal.name << std::endl;
    std::cout << "Specie: " << animal.specie << std::endl;
    std::cout << "Age: " << animal.age << std::endl;
    std::cout << "Weight[kg]: " << animal.weight_kg << " kg" << std::endl;
    std::cout << "---------------------------\n";
}

struct Person
{
    std::string name;
    int age;
    double height;
    StateOfBirth state;
    Animal pet;
};

void printPersonInfo(const Person person)
{
    std::string state;
    switch (person.state) {
        case State_China:
            state = "China";
            break;
        case State_France:
            state = "France";
            break;
        case State_Nigeria:
            state = "Nigeria";
            break;
        default:
            state = "Unknown";
            break;
    }

    // ­in order to access the individual members, we use the member selection operator " . "
    std::cout << "Name: " << person.name << std::endl;
    std::cout << "Age: " << person.age << std::endl;
    std::cout << "Height: " << person.height << " cm" << std::endl;
    std::cout << "State of Birth: " << state << std::endl;

    std::cout << "---------------------------\n";
}

int main()
{
    //* Initialize struct
    Person person1{ "Sophie Martin", 25, 160.7, State_France };
    Person person2 = { "Chinedu Okonkwo", 32, 182.3, State_Nigeria };

    //* Assign struct
    Person person3;
    person3.name = "Li Wei";
    person3.age = 28;
    person3.height = 168.2;
    person3.state = State_China;

    Person person4;
    person4 = { "Zhang Wei", 15, 170.0, State_China };

    // Print information of each person
    printPersonInfo(person1);
    printPersonInfo(person2);
    printPersonInfo(person3);
    printPersonInfo(person4);

    // Skip reassignment for some members
    person4 = { person4.name, 16, 175.0, person4.state };
    printPersonInfo(person4);

    //* Default initialization
    Animal animal1;
    printAnimalInfo(animal1);

    // Explicit values in a list initializer always take precedence over default member initialization values
    Animal animal2{ "Rex", "dog", 7, 25.5 };
    printAnimalInfo(animal2);

    //* Struct contains struct
    person1.pet = animal2;

    std::cout << "Pet's name: " << person1.pet.name << std::endl;
    std::cout << "Pet's specie: " << person1.pet.specie << std::endl;
    std::cout << "Pet's age: " << person1.pet.age << std::endl;
    std::cout << "Pet's Weight[kg]: " << person1.pet.weight_kg << std::endl;

    std::cout << "---------------------------\n";

    // Initialize struct with other struct
    Person person5{ "Gerard Deschamps", 50, 190.7, State_France, { "Cat", "Kitty", 1, 2 } };

    std::cout << "Pet's name: " << person5.pet.name << std::endl;
    std::cout << "Pet's specie: " << person5.pet.specie << std::endl;
    std::cout << "Pet's age: " << person5.pet.age << std::endl;
    std::cout << "Pet's Weight[kg]: " << person5.pet.weight_kg << std::endl;

    return 0;
}
