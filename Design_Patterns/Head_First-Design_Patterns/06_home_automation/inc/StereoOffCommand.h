#ifndef STEREOOFFCOMMAND_H
#define STEREOOFFCOMMAND_H

#include "Command.h"
#include "Stereo.h"

/**
 * @brief Concrete Command - Turn Stereo Off
 *
 * Encapsulates the request to turn a stereo off.
 */
class StereoOffCommand : public Command {
private:
    Stereo* stereo;  // Receiver

public:
    /**
     * @brief Constructor binds command to specific stereo receiver
     * @param s Pointer to Stereo receiver
     */
    explicit StereoOffCommand(Stereo* s) : stereo(s) {}

    /**
     * @brief Executes the command - turns stereo off
     */
    void execute() override {
        stereo->off();
    }

    /**
     * @brief Undoes the command - turns stereo back on
     *
     * Note: This is a simplified undo. A more sophisticated
     * implementation would restore previous volume, input mode, etc.
     */
    void undo() override {
        stereo->on();
    }
};

#endif // STEREOOFFCOMMAND_H
