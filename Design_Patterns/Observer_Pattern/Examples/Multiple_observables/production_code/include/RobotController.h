#pragma once

#include "IObservable.h"

class RobotController : public IObservable
{
public:
    void add(IObserver* observer) override;
    void remove(IObserver* observer) override;
    void notify() override;

    void setState(); // This function changes the state and notifies observers
    int getState() const { return state; }

private:
    int state = 0;
    std::vector<IObserver*> observers;
};
