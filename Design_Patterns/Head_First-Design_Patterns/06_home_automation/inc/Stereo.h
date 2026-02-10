#ifndef STEREO_H
#define STEREO_H

#include <string>
#include <iostream>

/**
 * @brief Receiver - Stereo system
 *
 * Another receiver with more complex operations than Light.
 * Demonstrates that receivers can have multiple methods that
 * commands can bind to.
 */
class Stereo {
private:
    std::string location;

public:
    explicit Stereo(const std::string& loc) : location(loc) {}

    /**
     * @brief Turns the stereo on
     */
    void on() {
        std::cout << location << " stereo is on" << std::endl;
    }

    /**
     * @brief Turns the stereo off
     */
    void off() {
        std::cout << location << " stereo is off" << std::endl;
    }

    /**
     * @brief Sets the stereo to CD mode
     */
    void setCD() {
        std::cout << location << " stereo is set for CD input" << std::endl;
    }

    /**
     * @brief Sets the stereo to DVD mode
     */
    void setDVD() {
        std::cout << location << " stereo is set for DVD input" << std::endl;
    }

    /**
     * @brief Sets the stereo to Radio mode
     */
    void setRadio() {
        std::cout << location << " stereo is set for Radio" << std::endl;
    }

    /**
     * @brief Sets the volume level
     * @param volume Volume level (0-100)
     */
    void setVolume(int volume) {
        std::cout << location << " stereo volume set to " << volume << std::endl;
    }

    /**
     * @brief Gets the stereo location
     * @return Stereo location string
     */
    std::string getLocation() const {
        return location;
    }
};

#endif // STEREO_H
