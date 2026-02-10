#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

/**
 * @brief Command Interface - Encapsulates a request as an object
 *
 * The Command interface declares methods for executing and undoing operations.
 * All concrete commands implement this interface, allowing the invoker to
 * work with any command without knowing its concrete type.
 */
class Command {
public:
    virtual ~Command() = default;

    /**
     * @brief Executes the encapsulated request
     *
     * Invokes the appropriate action on the receiver.
     */
    virtual void execute() = 0;

    /**
     * @brief Undoes the encapsulated request
     *
     * Reverses the action performed by execute().
     * Essential for undo/redo functionality.
     */
    virtual void undo() = 0;
};

#endif // COMMAND_H
