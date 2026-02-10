#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <iostream>

/**
 * @brief Subsystem Component - Theater Screen
 *
 * Part of the complex home theater subsystem.
 * Controls motorized screen positioning.
 */
class Screen {
private:
    std::string name;

public:
    explicit Screen(const std::string& n = "Theater Screen")
        : name(n) {}

    void down() {
        std::cout << name << " going down" << std::endl;
    }

    void up() {
        std::cout << name << " going up" << std::endl;
    }
};

#endif // SCREEN_H
