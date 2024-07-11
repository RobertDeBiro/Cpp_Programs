#pragma once

class IObservable;

class IObserver
{
public:
    virtual ~IObserver() = default;

    virtual void update(IObservable* observable) = 0;
};
