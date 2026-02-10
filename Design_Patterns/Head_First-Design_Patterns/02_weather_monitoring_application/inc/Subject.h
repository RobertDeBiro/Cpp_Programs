#ifndef SUBJECT_H
#define SUBJECT_H

class Observer;  // Forward declaration

// Subject interface - defines the observable object
// Maintains list of observers and notifies them of state changes
class Subject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};

#endif // SUBJECT_H
