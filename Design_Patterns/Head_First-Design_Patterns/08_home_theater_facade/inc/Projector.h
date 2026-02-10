#ifndef PROJECTOR_H
#define PROJECTOR_H

#include <string>
#include <iostream>

/**
 * @brief Subsystem Component - Projector
 *
 * Part of the complex home theater subsystem.
 * Controls video projection with various modes.
 */
class Projector {
private:
    std::string name;

public:
    explicit Projector(const std::string& n = "Top-O-Line Projector")
        : name(n) {}

    void on() {
        std::cout << name << " on" << std::endl;
    }

    void off() {
        std::cout << name << " off" << std::endl;
    }

    void wideScreenMode() {
        std::cout << name << " in widescreen mode (16x9 aspect ratio)" << std::endl;
    }

    void tvMode() {
        std::cout << name << " in TV mode (4x3 aspect ratio)" << std::endl;
    }
};

#endif // PROJECTOR_H
