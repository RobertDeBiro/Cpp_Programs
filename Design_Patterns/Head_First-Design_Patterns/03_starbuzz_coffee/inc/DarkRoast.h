#ifndef DARKROAST_H
#define DARKROAST_H

#include "Beverage.h"

// Concrete Component - Dark Roast coffee
class DarkRoast : public Beverage {
public:
    DarkRoast() {
        description = "Dark Roast";
    }

    double cost() const override {
        return 0.99;
    }
};

#endif // DARKROAST_H
