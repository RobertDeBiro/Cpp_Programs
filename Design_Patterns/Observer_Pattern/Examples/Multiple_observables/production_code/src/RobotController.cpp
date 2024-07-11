#include "RobotController.h"
#include "IObserver.h"
#include <iostream>

void RobotController::add(IObserver* observer)
{
    observers.push_back(observer);
}

void RobotController::remove(IObserver* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void RobotController::notify()
{
    for (auto observer : observers)
    {
        observer->update(this);
    }
}

void RobotController::setState()
{
    // Change state logic
    state++;
    std::cout << "RobotController state changed to: " << state << std::endl;
    notify();
}
