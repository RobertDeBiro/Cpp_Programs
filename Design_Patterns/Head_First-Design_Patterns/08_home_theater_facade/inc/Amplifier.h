#ifndef AMPLIFIER_H
#define AMPLIFIER_H

#include <string>
#include <iostream>

// Forward declaration
class DvdPlayer;
class CdPlayer;
class Tuner;

/**
 * @brief Subsystem Component - Amplifier
 *
 * Part of the complex home theater subsystem.
 * Has many methods that must be called in correct sequence.
 */
class Amplifier {
private:
    std::string name;

public:
    explicit Amplifier(const std::string& n = "Top-O-Line Amplifier")
        : name(n) {}

    void on() {
        std::cout << name << " on" << std::endl;
    }

    void off() {
        std::cout << name << " off" << std::endl;
    }

    void setDvd([[maybe_unused]] DvdPlayer* dvd) {
        std::cout << name << " setting DVD player to Top-O-Line DVD Player" << std::endl;
    }

    void setCd([[maybe_unused]] CdPlayer* cd) {
        std::cout << name << " setting CD player" << std::endl;
    }

    void setTuner([[maybe_unused]] Tuner* tuner) {
        std::cout << name << " setting tuner" << std::endl;
    }

    void setSurroundSound() {
        std::cout << name << " surround sound on (5 speakers, 1 subwoofer)" << std::endl;
    }

    void setStereoSound() {
        std::cout << name << " stereo mode on" << std::endl;
    }

    void setVolume(int level) {
        std::cout << name << " setting volume to " << level << std::endl;
    }
};

#endif // AMPLIFIER_H
