#ifndef IOBSERVER_HPP
#define IOBSERVER_HPP

class IObserver
{
public:
    virtual void update() = 0;
    virtual ~IObserver() = default;
};

#endif