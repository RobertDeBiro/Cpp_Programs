#ifndef DVDPLAYER_H
#define DVDPLAYER_H

#include <string>
#include <iostream>

/**
 * @brief Subsystem Component - DVD Player
 *
 * Part of the complex home theater subsystem.
 * Manages DVD playback with multiple state transitions.
 */
class DvdPlayer {
private:
    std::string name;
    std::string currentMovie;

public:
    explicit DvdPlayer(const std::string& n = "Top-O-Line DVD Player")
        : name(n), currentMovie("") {}

    void on() {
        std::cout << name << " on" << std::endl;
    }

    void off() {
        std::cout << name << " off" << std::endl;
    }

    void play(const std::string& movie) {
        currentMovie = movie;
        std::cout << name << " playing \"" << movie << "\"" << std::endl;
    }

    void stop() {
        std::cout << name << " stopped \"" << currentMovie << "\"" << std::endl;
        currentMovie = "";
    }

    void eject() {
        if (!currentMovie.empty()) {
            std::cout << name << " ejecting \"" << currentMovie << "\"" << std::endl;
            currentMovie = "";
        } else {
            std::cout << name << " eject" << std::endl;
        }
    }

    void pause() {
        std::cout << name << " paused \"" << currentMovie << "\"" << std::endl;
    }
};

#endif // DVDPLAYER_H
