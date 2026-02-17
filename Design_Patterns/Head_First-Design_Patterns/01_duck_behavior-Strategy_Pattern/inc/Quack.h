#ifndef QUACK_H
#define QUACK_H

#include "QuackBehavior.h"
#include <iostream>

// Concrete strategy for standard quacking
class Quack : public QuackBehavior {
public:
    void quack() const override {
        std::cout << "Quack\n";
    }
};

#endif // QUACK_H
