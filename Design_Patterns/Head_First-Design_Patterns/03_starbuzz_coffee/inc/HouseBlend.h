#ifndef HOUSEBLEND_H
#define HOUSEBLEND_H

#include "Beverage.h"

// Concrete Component - House Blend coffee
class HouseBlend : public Beverage {
public:
    HouseBlend() {
        description = "House Blend Coffee";
    }

    double cost() const override {
        return 0.89;
    }
};

#endif // HOUSEBLEND_H
