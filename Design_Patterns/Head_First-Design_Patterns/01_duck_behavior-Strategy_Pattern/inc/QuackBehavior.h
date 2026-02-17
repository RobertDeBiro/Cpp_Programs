#ifndef QUACKBEHAVIOR_H
#define QUACKBEHAVIOR_H

// Interface for quacking behaviors
// Defines a family of quacking algorithms
class QuackBehavior {
public:
    virtual void quack() const = 0;
    virtual ~QuackBehavior() = default;
};

#endif // QUACKBEHAVIOR_H
