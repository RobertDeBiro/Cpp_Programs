#ifndef LIGHTOFFCOMMAND_H
#define LIGHTOFFCOMMAND_H

#include "Command.h"
#include "Light.h"

/**
 * @brief Concrete Command - Turn Light Off
 *
 * Encapsulates the request to turn a light off.
 * Binds a Light receiver with the off() action.
 */
class LightOffCommand : public Command {
private:
    Light* light;  // Receiver

public:
    /**
     * @brief Constructor binds command to specific light receiver
     * @param l Pointer to Light receiver
     */
    explicit LightOffCommand(Light* l) : light(l) {}

    /**
     * @brief Executes the command - turns light off
     */
    void execute() override {
        light->off();
    }

    /**
     * @brief Undoes the command - turns light on
     */
    void undo() override {
        light->on();
    }
};

#endif // LIGHTOFFCOMMAND_H
