#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "FlyBehavior.h"
#include <iostream>

// Concrete strategy for flying with wings
class FlyWithWings : public FlyBehavior {
public:
    void fly() const override {
        std::cout << "I'm flying!!\n";
    }
};

#endif // FLYWITHWINGS_H
