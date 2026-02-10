#ifndef NOCOMMAND_H
#define NOCOMMAND_H

#include "Command.h"

/**
 * @brief Null Object Pattern - NoCommand
 *
 * A command that does nothing. This is an example of the Null Object pattern.
 * Used to initialize command slots so we don't have to check for nullptr.
 *
 * Benefits:
 * - Eliminates null checks in invoker code
 * - Provides default "do nothing" behavior
 * - Cleaner code: remoteControl.execute(slot) always works
 */
class NoCommand : public Command {
public:
    /**
     * @brief Execute does nothing (null object)
     */
    void execute() override {
        // Intentionally empty - null object pattern
    }

    /**
     * @brief Undo does nothing (null object)
     */
    void undo() override {
        // Intentionally empty - null object pattern
    }
};

#endif // NOCOMMAND_H
