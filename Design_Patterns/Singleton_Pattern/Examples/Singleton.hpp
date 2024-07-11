#include <iostream>

class Singleton
{
    static Singleton* instance;

    // Singleton class has PRIVATE CONSTRUCTOR
    //  - another possible approach is to put constructor declaration into 'public'
    //    but also to declare it with 'delete' keyword
    Singleton() {};

public:
    static Singleton* getInstance()
    {
        if(instance == nullptr)
        {
            std::cout << "Creating Singleton instance.\n";
            instance = new Singleton();
            std::cout << "Singleton instance address: " << instance << std::endl;
        }
        else
        {
            std::cout << "Creation of instance ignored: singleton instance already exists!\n";
        }

        return instance; 
    }
};

// static member variable needs to be initialized, and that needs to be done
// apart from class definition
Singleton* Singleton::instance{nullptr};