#pragma once

#include <vector>
#include <algorithm>

class IObserver;

class IObservable
{
public:
    virtual ~IObservable() = default;

    virtual void add(IObserver* observer) = 0;
    virtual void remove(IObserver* observer) = 0;
    virtual void notify() = 0;
};
