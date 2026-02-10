#ifndef WILDTURKEY_H
#define WILDTURKEY_H

#include "Turkey.h"
#include <iostream>

/**
 * @brief Concrete implementation of Turkey interface
 *
 * This is a turkey with incompatible interface to Duck.
 * Turkeys gobble (don't quack) and fly short distances.
 */
class WildTurkey : public Turkey {
public:
    /**
     * @brief Turkey makes gobble sound (not quack)
     */
    void gobble() override {
        std::cout << "Gobble gobble" << std::endl;
    }

    /**
     * @brief Turkey flies short distance (not long flight like duck)
     */
    void fly() override {
        std::cout << "I'm flying a short distance" << std::endl;
    }
};

#endif // WILDTURKEY_H
