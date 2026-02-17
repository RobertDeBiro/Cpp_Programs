#ifndef MUTEQUACK_H
#define MUTEQUACK_H

#include "QuackBehavior.h"
#include <iostream>

// Concrete strategy for silent quacking
class MuteQuack : public QuackBehavior {
public:
    void quack() const override {
        std::cout << "<<Silence>>\n";
    }
};

#endif // MUTEQUACK_H
