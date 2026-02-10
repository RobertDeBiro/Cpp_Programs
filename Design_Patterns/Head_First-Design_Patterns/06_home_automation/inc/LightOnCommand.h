#ifndef LIGHTONCOMMAND_H
#define LIGHTONCOMMAND_H

#include "Command.h"
#include "Light.h"

/**
 * @brief Concrete Command - Turn Light On
 *
 * Encapsulates the request to turn a light on.
 * Binds a Light receiver with the on() action.
 */
class LightOnCommand : public Command {
private:
    Light* light;  // Receiver

public:
    /**
     * @brief Constructor binds command to specific light receiver
     * @param l Pointer to Light receiver
     */
    explicit LightOnCommand(Light* l) : light(l) {}

    /**
     * @brief Executes the command - turns light on
     */
    void execute() override {
        light->on();
    }

    /**
     * @brief Undoes the command - turns light off
     */
    void undo() override {
        light->off();
    }
};

#endif // LIGHTONCOMMAND_H
