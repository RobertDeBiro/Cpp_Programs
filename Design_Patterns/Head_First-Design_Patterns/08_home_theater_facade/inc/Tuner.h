#ifndef TUNER_H
#define TUNER_H

#include <string>
#include <iostream>

/**
 * @brief Subsystem Component - Tuner
 *
 * Part of the complex home theater subsystem.
 * Radio/TV tuner component (simplified).
 */
class Tuner {
private:
    std::string name;

public:
    explicit Tuner(const std::string& n = "Top-O-Line Tuner")
        : name(n) {}

    void on() {
        std::cout << name << " on" << std::endl;
    }

    void off() {
        std::cout << name << " off" << std::endl;
    }

    void setFrequency(double freq) {
        std::cout << name << " setting frequency to " << freq << std::endl;
    }

    void setAm() {
        std::cout << name << " setting AM mode" << std::endl;
    }

    void setFm() {
        std::cout << name << " setting FM mode" << std::endl;
    }
};

#endif // TUNER_H
