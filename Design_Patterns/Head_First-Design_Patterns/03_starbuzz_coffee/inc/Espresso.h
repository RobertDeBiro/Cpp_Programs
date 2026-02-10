#ifndef ESPRESSO_H
#define ESPRESSO_H

#include "Beverage.h"

// Concrete Component - Espresso beverage
class Espresso : public Beverage {
public:
    Espresso() {
        description = "Espresso";
    }

    double cost() const override {
        return 1.99;
    }
};

#endif // ESPRESSO_H
