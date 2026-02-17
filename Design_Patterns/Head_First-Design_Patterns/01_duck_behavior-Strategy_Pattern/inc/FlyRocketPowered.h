#ifndef FLYROCKETPOWERED_H
#define FLYROCKETPOWERED_H

#include "FlyBehavior.h"
#include <iostream>

// Concrete strategy for rocket-powered flying
class FlyRocketPowered : public FlyBehavior {
public:
    void fly() const override {
        std::cout << "I'm flying with a rocket!\n";
    }
};

#endif // FLYROCKETPOWERED_H
