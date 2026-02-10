#ifndef OBSERVER_H
#define OBSERVER_H

// Observer interface - defines update method that all observers must implement
// This is the core of the Observer pattern: observers are notified via this interface
class Observer {
public:
    virtual void update(float temperature, float humidity, float pressure) = 0;
    virtual ~Observer() = default;
};

#endif // OBSERVER_H
