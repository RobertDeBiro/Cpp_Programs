#ifndef CDPLAYER_H
#define CDPLAYER_H

#include <string>
#include <iostream>

/**
 * @brief Subsystem Component - CD Player
 *
 * Part of the complex home theater subsystem.
 * CD player component (simplified).
 */
class CdPlayer {
private:
    std::string name;

public:
    explicit CdPlayer(const std::string& n = "Top-O-Line CD Player")
        : name(n) {}

    void on() {
        std::cout << name << " on" << std::endl;
    }

    void off() {
        std::cout << name << " off" << std::endl;
    }

    void play(const std::string& title) {
        std::cout << name << " playing \"" << title << "\"" << std::endl;
    }

    void stop() {
        std::cout << name << " stopped" << std::endl;
    }

    void eject() {
        std::cout << name << " eject" << std::endl;
    }
};

#endif // CDPLAYER_H
