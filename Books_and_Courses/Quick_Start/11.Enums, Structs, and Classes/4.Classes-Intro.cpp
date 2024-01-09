//* Class
/**
 *  - user-defined data type that can contain attributes and methods
 *  - syntax:
 *?     class Class_name
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
 *  - class definitions are like a blueprint - they describe what the resulting object
 *    will look like, but they do not actually create the object
 *  - when we define a variable of a class, we call it instantiating the class
 *    while variable itself is called instance of the class or object
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

class Animal
{
public:
    std::string m_name{ "Beethoven" };
    std::string m_specie{ "Dog" };
    int m_age{ 5 };
    double m_weight_kg{ 20.2 };

    void printAnimalInfo()
    {
        std::cout << "Name: " << m_name << std::endl;
        std::cout << "Specie: " << m_specie << std::endl;
        std::cout << "Age: " << m_age << std::endl;
        std::cout << "Weight[kg]: " << m_weight_kg << " kg" << std::endl;
        std::cout << "---------------------------\n";
    }
};

class Person
{
public:
    //* Member attributes
    std::string m_name;
    int m_age;
    double m_height;
    StateOfBirth m_state;
    Animal m_pet;
    double m_money;

    //* Member functions
    void printPersonInfo();
    void addMoney(double val);
    double getMoney() { return m_money; }
};

// Member functions can be also defined outside the class definition
void Person::printPersonInfo()
{
    std::string state;
    switch (m_state) {
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

    std::cout << "Name: " << m_name << std::endl;
    std::cout << "Age: " << m_age << std::endl;
    std::cout << "Height: " << m_height << " cm" << std::endl;
    std::cout << "State of Birth: " << state << std::endl;

    std::cout << "----------- Pet: ----------- \n";
    m_pet.printAnimalInfo();
}

void Person::addMoney(double val)
{
    m_money += val;
}

int main()
{
    //* Initialize classes
    Animal animal{ "Rex", "dog", 7, 25.5 }; // memory allocated
    Person person{ "Sophie Martin", 25, 160.7, State_France, animal, 10'000 };

    animal.printAnimalInfo();
    person.printPersonInfo();

    double money = 3500.5;
    person.addMoney(money);

    std::cout << "Current amount of money: " << person.getMoney() << '\n';

    return 0;
}
