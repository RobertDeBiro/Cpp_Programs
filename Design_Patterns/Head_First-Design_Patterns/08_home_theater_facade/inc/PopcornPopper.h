#ifndef POPCORNPOPPER_H
#define POPCORNPOPPER_H

#include <string>
#include <iostream>

/**
 * @brief Subsystem Component - Popcorn Popper
 *
 * Part of the complex home theater subsystem.
 * Controls popcorn making functionality.
 */
class PopcornPopper {
private:
    std::string name;

public:
    explicit PopcornPopper(const std::string& n = "Popcorn Popper")
        : name(n) {}

    void on() {
        std::cout << name << " on" << std::endl;
    }

    void off() {
        std::cout << name << " off" << std::endl;
    }

    void pop() {
        std::cout << name << " popping popcorn!" << std::endl;
    }
};

#endif // POPCORNPOPPER_H
