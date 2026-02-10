#ifndef FLYBEHAVIOR_H
#define FLYBEHAVIOR_H

// Interface for flying behaviors
// Defines a family of flying algorithms
class FlyBehavior {
public:
    virtual void fly() const = 0;
    virtual ~FlyBehavior() = default;
};

#endif // FLYBEHAVIOR_H
