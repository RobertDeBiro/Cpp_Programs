#ifndef FLYNOWAY_H
#define FLYNOWAY_H

#include "FlyBehavior.h"
#include <iostream>

// Concrete strategy for no flying ability
class FlyNoWay : public FlyBehavior {
public:
    void fly() const override {
        std::cout << "I can't fly\n";
    }
};

#endif // FLYNOWAY_H
