#ifndef STEREOONWITHCDCOMMAND_H
#define STEREOONWITHCDCOMMAND_H

#include "Command.h"
#include "Stereo.h"

/**
 * @brief Concrete Command - Turn Stereo On with CD
 *
 * Demonstrates a command that performs multiple operations on a receiver.
 * This command turns on the stereo, sets it to CD mode, and sets volume.
 */
class StereoOnWithCDCommand : public Command {
private:
    Stereo* stereo;  // Receiver

public:
    /**
     * @brief Constructor binds command to specific stereo receiver
     * @param s Pointer to Stereo receiver
     */
    explicit StereoOnWithCDCommand(Stereo* s) : stereo(s) {}

    /**
     * @brief Executes the command - turn on, set CD, set volume
     *
     * This demonstrates that a single command can invoke
     * multiple operations on the receiver.
     */
    void execute() override {
        stereo->on();
        stereo->setCD();
        stereo->setVolume(11);
    }

    /**
     * @brief Undoes the command - turns stereo off
     *
     * Undo doesn't need to reverse every operation,
     * just return to a reasonable previous state.
     */
    void undo() override {
        stereo->off();
    }
};

#endif // STEREOONWITHCDCOMMAND_H
