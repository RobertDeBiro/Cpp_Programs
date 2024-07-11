#pragma once

#include "IObserver.h"
#include "PLController.h"
#include "RobotController.h"

class AlarmManager : public IObserver
{
public:
    void update(IObservable* observable) override;
};
