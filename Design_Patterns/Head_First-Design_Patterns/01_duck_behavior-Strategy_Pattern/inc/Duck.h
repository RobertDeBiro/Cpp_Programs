#ifndef DUCK_H
#define DUCK_H

#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include <memory>
#include <iostream>

// Context class that uses strategy pattern
// Duck HAS-A FlyBehavior and HAS-A QuackBehavior (composition over inheritance)
class Duck {
protected:
    std::unique_ptr<FlyBehavior> flyBehavior;
    std::unique_ptr<QuackBehavior> quackBehavior;

public:
    Duck() = default;
    virtual ~Duck() = default;

    // Pure virtual - each duck type displays differently
    virtual void display() const = 0;

    // Delegate to behavior strategies
    void performFly() const {
        if (flyBehavior) {
            flyBehavior->fly();
        }
    }

    void performQuack() const {
        if (quackBehavior) {
            quackBehavior->quack();
        }
    }

    void swim() const {
        std::cout << "All ducks float, even decoys!\n";
    }

    // Runtime behavior change - the power of Strategy pattern!
    void setFlyBehavior(std::unique_ptr<FlyBehavior> fb) {
        flyBehavior = std::move(fb);
    }

    void setQuackBehavior(std::unique_ptr<QuackBehavior> qb) {
        quackBehavior = std::move(qb);
    }
};

#endif // DUCK_H
