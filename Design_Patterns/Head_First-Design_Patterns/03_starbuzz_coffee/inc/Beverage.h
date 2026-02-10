#ifndef BEVERAGE_H
#define BEVERAGE_H

#include <string>

// Abstract Component - base class for all beverages
// Defines the interface that both concrete beverages and decorators must implement
class Beverage {
protected:
    std::string description = "Unknown Beverage";

public:
    virtual ~Beverage() = default;

    virtual std::string getDescription() const {
        return description;
    }

    // Pure virtual - must be implemented by concrete classes
    virtual double cost() const = 0;
};

#endif // BEVERAGE_H
