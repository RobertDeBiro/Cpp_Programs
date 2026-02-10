#ifndef MACROCOMMAND_H
#define MACROCOMMAND_H

#include "Command.h"
#include <vector>
#include <memory>

/**
 * @brief Composite Command - MacroCommand
 *
 * A MacroCommand is a command that executes multiple commands in sequence.
 * This demonstrates the Composite pattern combined with Command pattern.
 *
 * Use cases:
 * - "Party mode": Turn on lights, stereo, set volume, dim lights
 * - "Movie mode": Dim lights, turn on TV, close blinds
 * - Batch operations: Execute multiple commands atomically
 */
class MacroCommand : public Command {
private:
    std::vector<std::shared_ptr<Command>> commands;

public:
    /**
     * @brief Constructor accepts a vector of commands
     * @param cmds Vector of commands to execute in sequence
     */
    explicit MacroCommand(const std::vector<std::shared_ptr<Command>>& cmds)
        : commands(cmds) {}

    /**
     * @brief Executes all commands in sequence
     *
     * Iterates through the command vector and executes each one.
     */
    void execute() override {
        for (auto& cmd : commands) {
            cmd->execute();
        }
    }

    /**
     * @brief Undoes all commands in reverse order
     *
     * To properly undo a sequence of commands, we must undo them
     * in REVERSE order. This maintains correct state transitions.
     *
     * Example: If we turned on lights THEN turned on stereo,
     * we should turn off stereo THEN turn off lights to undo.
     */
    void undo() override {
        for (auto it = commands.rbegin(); it != commands.rend(); ++it) {
            (*it)->undo();
        }
    }
};

#endif // MACROCOMMAND_H
