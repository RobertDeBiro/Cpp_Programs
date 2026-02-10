#ifndef SQUEAK_H
#define SQUEAK_H

#include "QuackBehavior.h"
#include <iostream>

// Concrete strategy for squeaking (rubber ducks)
class Squeak : public QuackBehavior {
public:
    void quack() const override {
        std::cout << "Squeak\n";
    }
};

#endif // SQUEAK_H
