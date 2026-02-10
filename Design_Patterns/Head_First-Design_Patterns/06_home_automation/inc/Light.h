#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include <iostream>

/**
 * @brief Receiver - Light device
 *
 * The Light class is a receiver in the Command pattern.
 * It knows how to perform the actual work (turning on/off).
 * Commands bind to receivers and invoke their methods.
 */
class Light {
private:
    std::string location;

public:
    explicit Light(const std::string& loc) : location(loc) {}

    /**
     * @brief Turns the light on
     */
    void on() {
        std::cout << location << " light is on" << std::endl;
    }

    /**
     * @brief Turns the light off
     */
    void off() {
        std::cout << location << " light is off" << std::endl;
    }

    /**
     * @brief Gets the light location
     * @return Light location string
     */
    std::string getLocation() const {
        return location;
    }
};

#endif // LIGHT_H
