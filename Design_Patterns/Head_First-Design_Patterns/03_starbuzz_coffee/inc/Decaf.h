#ifndef DECAF_H
#define DECAF_H

#include "Beverage.h"

// Concrete Component - Decaf coffee
class Decaf : public Beverage {
public:
    Decaf() {
        description = "Decaf";
    }

    double cost() const override {
        return 1.05;
    }
};

#endif // DECAF_H
