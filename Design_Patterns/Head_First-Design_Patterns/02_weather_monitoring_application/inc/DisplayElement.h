#ifndef DISPLAYELEMENT_H
#define DISPLAYELEMENT_H

// DisplayElement interface - all display elements must implement display()
// Separates display responsibility from observation responsibility
class DisplayElement {
public:
    virtual void display() const = 0;
    virtual ~DisplayElement() = default;
};

#endif // DISPLAYELEMENT_H
