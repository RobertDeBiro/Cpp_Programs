#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include "Duck.h"
#include "FlyWithWings.h"
#include "Quack.h"

// Concrete duck type
// Demonstrates composition: MallardDuck HAS-A FlyWithWings, HAS-A Quack
class MallardDuck : public Duck {
public:
    MallardDuck() {
        // Set behaviors at construction time
        flyBehavior = std::make_unique<FlyWithWings>();
        quackBehavior = std::make_unique<Quack>();
    }

    void display() const override {
        std::cout << "I'm a real Mallard duck\n";
    }
};

#endif // MALLARDDUCK_H
