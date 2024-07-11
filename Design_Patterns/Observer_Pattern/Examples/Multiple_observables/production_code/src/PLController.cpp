#include "PLController.h"
#include "IObserver.h"
#include <iostream>

void PLController::add(IObserver* observer)
{
    observers.push_back(observer);
}

void PLController::remove(IObserver* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void PLController::notify()
{
    for (auto observer : observers)
    {
        observer->update(this);
    }
}

void PLController::setState()
{
    // Change state logic
    state++;
    std::cout << "PLController state changed to: " << state << std::endl;
    notify();
}
