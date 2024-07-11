#include "AlarmManager.h"
#include <iostream>

void AlarmManager::update(IObservable* observable)
{
    if (auto plController = dynamic_cast<PLController*>(observable))
    {
        std::cout << "AlarmManager received update from PLController: " << plController->getState() << std::endl;
    }
    else if (auto robotController = dynamic_cast<RobotController*>(observable))
    {
        std::cout << "AlarmManager received update from RobotController: " << robotController->getState() << std::endl;
    }
}
