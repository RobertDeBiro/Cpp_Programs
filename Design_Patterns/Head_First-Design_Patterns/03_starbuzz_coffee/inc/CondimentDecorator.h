#ifndef CONDIMENTDECORATOR_H
#define CONDIMENTDECORATOR_H

#include "Beverage.h"
#include <memory>

// Abstract Decorator - base class for all condiment decorators
// Extends Beverage AND contains a Beverage (IS-A and HAS-A relationship)
class CondimentDecorator : public Beverage {
public:
    // Force derived decorators to implement getDescription
    virtual std::string getDescription() const override = 0;
    virtual ~CondimentDecorator() = default;
};

#endif // CONDIMENTDECORATOR_H
