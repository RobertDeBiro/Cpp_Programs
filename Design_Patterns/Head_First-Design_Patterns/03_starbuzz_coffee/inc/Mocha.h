#ifndef MOCHA_H
#define MOCHA_H

#include "CondimentDecorator.h"
#include <memory>

// Concrete Decorator - adds Mocha to a beverage
// Wraps a beverage and adds mocha cost + description
class Mocha : public CondimentDecorator {
private:
    std::unique_ptr<Beverage> beverage;  // Owns the wrapped beverage

public:
    // Constructor takes ownership of the beverage via move semantics
    explicit Mocha(std::unique_ptr<Beverage> b) : beverage(std::move(b)) {}

    std::string getDescription() const override {
        return beverage->getDescription() + ", Mocha";
    }

    double cost() const override {
        return 0.20 + beverage->cost();  // Delegate to wrapped beverage
    }
};

#endif // MOCHA_H
