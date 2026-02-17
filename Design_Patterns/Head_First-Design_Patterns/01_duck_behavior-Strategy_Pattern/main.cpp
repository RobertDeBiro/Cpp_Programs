#include "MallardDuck.h"
#include "ModelDuck.h"
#include "FlyRocketPowered.h"
#include <memory>
#include <iostream>

int main() {
    // Create a mallard duck
    std::unique_ptr<Duck> mallard = std::make_unique<MallardDuck>();

    std::cout << "=== Mallard Duck ===" << std::endl;
    mallard->performQuack();
    mallard->performFly();

    std::cout << "\n=== Model Duck ===" << std::endl;

    // Create a model duck
    std::unique_ptr<Duck> model = std::make_unique<ModelDuck>();

    // Initially can't fly
    model->performFly();

    // Dynamic behavior change at runtime!
    // This is the power of Strategy pattern
    std::cout << "\n--- Attaching rocket to model duck ---" << std::endl;
    model->setFlyBehavior(std::make_unique<FlyRocketPowered>());
    model->performFly();

    return 0;
}
