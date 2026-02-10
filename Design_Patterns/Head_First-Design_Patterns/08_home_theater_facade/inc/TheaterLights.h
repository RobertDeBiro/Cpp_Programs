#ifndef THEATERLIGHTS_H
#define THEATERLIGHTS_H

#include <string>
#include <iostream>

/**
 * @brief Subsystem Component - Theater Lights
 *
 * Part of the complex home theater subsystem.
 * Controls lighting with dimming capabilities.
 */
class TheaterLights {
private:
    std::string name;

public:
    explicit TheaterLights(const std::string& n = "Theater Ceiling Lights")
        : name(n) {}

    void on() {
        std::cout << name << " on" << std::endl;
    }

    void off() {
        std::cout << name << " off" << std::endl;
    }

    void dim(int level) {
        std::cout << name << " dimming to " << level << "%" << std::endl;
    }
};

#endif // THEATERLIGHTS_H
