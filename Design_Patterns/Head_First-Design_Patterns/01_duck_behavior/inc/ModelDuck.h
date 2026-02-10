#ifndef MODELDUCK_H
#define MODELDUCK_H

#include "Duck.h"
#include "FlyNoWay.h"
#include "Quack.h"

// Concrete duck type for model/toy ducks
// Initially can't fly, but can have behavior changed at runtime
class ModelDuck : public Duck {
public:
    ModelDuck() {
        flyBehavior = std::make_unique<FlyNoWay>();
        quackBehavior = std::make_unique<Quack>();
    }

    void display() const override {
        std::cout << "I'm a model duck\n";
    }
};

#endif // MODELDUCK_H
