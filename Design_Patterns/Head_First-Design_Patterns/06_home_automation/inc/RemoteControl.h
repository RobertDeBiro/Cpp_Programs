#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include "Command.h"
#include "NoCommand.h"
#include <memory>
#include <array>
#include <iostream>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

/**
 * @brief Invoker - Remote Control with Undo
 *
 * The RemoteControl is the invoker in the Command pattern.
 * It holds references to Command objects and invokes them
 * without knowing their concrete types or receivers.
 *
 * Features:
 * - 7 programmable slots (on/off pairs)
 * - Undo functionality for last executed command
 * - Uses Null Object pattern to avoid nullptr checks
 */
class RemoteControl {
private:
    static constexpr int NUM_SLOTS = 7;

    // Command storage using std::shared_ptr for safe sharing
    std::array<std::shared_ptr<Command>, NUM_SLOTS> onCommands;
    std::array<std::shared_ptr<Command>, NUM_SLOTS> offCommands;
    std::shared_ptr<Command> undoCommand;

public:
    /**
     * @brief Constructor initializes all slots with NoCommand
     *
     * Uses Null Object pattern so we never have to check for nullptr.
     */
    RemoteControl() {
        auto noCommand = std::make_shared<NoCommand>();

        for (int i = 0; i < NUM_SLOTS; ++i) {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }

        undoCommand = noCommand;
    }

    /**
     * @brief Sets commands for a specific slot
     *
     * @param slot Slot number (0-6)
     * @param onCommand Command to execute when On button pressed
     * @param offCommand Command to execute when Off button pressed
     */
    void setCommand(int slot,
                   std::shared_ptr<Command> onCommand,
                   std::shared_ptr<Command> offCommand) {
        if (slot < 0 || slot >= NUM_SLOTS) {
            std::cerr << "Invalid slot number: " << slot << std::endl;
            return;
        }

        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }

    /**
     * @brief Executes the On command for a slot
     *
     * @param slot Slot number (0-6)
     */
    void onButtonWasPushed(int slot) {
        if (slot < 0 || slot >= NUM_SLOTS) {
            std::cerr << "Invalid slot number: " << slot << std::endl;
            return;
        }

        onCommands[slot]->execute();
        undoCommand = onCommands[slot];  // Save for undo
    }

    /**
     * @brief Executes the Off command for a slot
     *
     * @param slot Slot number (0-6)
     */
    void offButtonWasPushed(int slot) {
        if (slot < 0 || slot >= NUM_SLOTS) {
            std::cerr << "Invalid slot number: " << slot << std::endl;
            return;
        }

        offCommands[slot]->execute();
        undoCommand = offCommands[slot];  // Save for undo
    }

    /**
     * @brief Undoes the last executed command
     *
     * This demonstrates the undo functionality of the Command pattern.
     * The invoker doesn't know HOW to undo - it just calls undo() on
     * the last command object.
     */
    void undoButtonWasPushed() {
        undoCommand->undo();
    }

    /**
     * @brief Prints the remote control configuration
     *
     * Shows which commands are assigned to each slot.
     * Uses RTTI (typeid) to display command class names.
     *
     * @return String representation of remote control state
     */
    std::string toString() const {
        std::string result = "\n----- Remote Control -----\n";

        for (int i = 0; i < NUM_SLOTS; ++i) {
            result += "[slot " + std::to_string(i) + "] ";
            result += getCommandName(onCommands[i].get());
            result += "     ";
            result += getCommandName(offCommands[i].get());
            result += "\n";
        }

        result += "[undo] ";
        result += getCommandName(undoCommand.get());
        result += "\n";

        return result;
    }

private:
    /**
     * @brief Helper to get command class name
     *
     * Uses C++ RTTI to extract class name for display.
     *
     * @param cmd Command pointer
     * @return Command class name
     */
    std::string getCommandName(const Command* cmd) const {
        if (!cmd) return "nullptr";

        std::string name = typeid(*cmd).name();

        // Demangle name on GCC/Clang
        #ifdef __GNUG__
            int status = 0;
            char* demangled = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);
            if (status == 0 && demangled) {
                name = demangled;
                free(demangled);
            }
        #endif

        return name;
    }
};

// Provide stream output operator
inline std::ostream& operator<<(std::ostream& os, const RemoteControl& rc) {
    os << rc.toString();
    return os;
}

#endif // REMOTECONTROL_H
