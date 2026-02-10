#ifndef WHIP_H
#define WHIP_H

#include "CondimentDecorator.h"
#include <memory>

// Concrete Decorator - adds Whipped cream to a beverage
class Whip : public CondimentDecorator {
private:
    std::unique_ptr<Beverage> beverage;

public:
    explicit Whip(std::unique_ptr<Beverage> b) : beverage(std::move(b)) {}

    std::string getDescription() const override {
        return beverage->getDescription() + ", Whip";
    }

    double cost() const override {
        return 0.10 + beverage->cost();
    }
};

#endif // WHIP_H
