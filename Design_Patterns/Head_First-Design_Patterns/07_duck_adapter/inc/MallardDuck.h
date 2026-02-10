#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include "Duck.h"
#include <iostream>

/**
 * @brief Concrete implementation of Duck interface
 *
 * This is a standard duck that implements the Duck interface
 * as expected by client code.
 */
class MallardDuck : public Duck {
public:
    /**
     * @brief Standard duck quack
     */
    void quack() override {
        std::cout << "Quack" << std::endl;
    }

    /**
     * @brief Standard duck flight
     */
    void fly() override {
        std::cout << "I'm flying" << std::endl;
    }
};

#endif // MALLARDDUCK_H
