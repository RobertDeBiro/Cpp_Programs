#ifndef SOY_H
#define SOY_H

#include "CondimentDecorator.h"
#include <memory>

// Concrete Decorator - adds Soy milk to a beverage
class Soy : public CondimentDecorator {
private:
    std::unique_ptr<Beverage> beverage;

public:
    explicit Soy(std::unique_ptr<Beverage> b) : beverage(std::move(b)) {}

    std::string getDescription() const override {
        return beverage->getDescription() + ", Soy";
    }

    double cost() const override {
        return 0.15 + beverage->cost();
    }
};

#endif // SOY_H
