/**
 * @file main.cpp
 * @brief Command Pattern - Home Automation Remote Control Demonstration
 *
 * Demonstrates the Command pattern where:
 * - Command is the abstract command interface
 * - LightOnCommand, LightOffCommand, etc. are Concrete Commands
 * - Light, Stereo are Receivers (know how to perform actual work)
 * - RemoteControl is the Invoker (asks commands to execute)
 * - main() is the Client (creates commands and configures invoker)
 *
 * Key Points:
 * - Invoker is decoupled from receivers (doesn't know about Light or Stereo)
 * - Commands encapsulate requests as objects (can be stored, queued, logged)
 * - Undo functionality supported (commands know how to reverse themselves)
 * - Null Object pattern eliminates nullptr checks (NoCommand)
 * - Macro commands demonstrate composite pattern (multiple operations)
 */

#include "RemoteControl.h"
#include "Light.h"
#include "Stereo.h"
#include "LightOnCommand.h"
#include "LightOffCommand.h"
#include "StereoOnWithCDCommand.h"
#include "StereoOffCommand.h"
#include "MacroCommand.h"
#include <iostream>
#include <memory>
#include <vector>

void demonstrateBasicCommands();
void demonstrateUndoFunctionality();
void demonstrateMacroCommands();

int main() {
    std::cout << "=== Command Pattern - Home Automation Remote Control ===" << std::endl;
    std::cout << std::endl;

    demonstrateBasicCommands();
    std::cout << std::endl;

    demonstrateUndoFunctionality();
    std::cout << std::endl;

    demonstrateMacroCommands();
    std::cout << std::endl;

    std::cout << "=== Demonstration Complete ===" << std::endl;
    std::cout << std::endl;

    std::cout << "Key Observations:" << std::endl;
    std::cout << "1. RemoteControl doesn't know about Light or Stereo classes" << std::endl;
    std::cout << "2. Commands encapsulate requests as objects (first-class citizens)" << std::endl;
    std::cout << "3. Undo works because commands know how to reverse operations" << std::endl;
    std::cout << "4. Null Object pattern (NoCommand) eliminates nullptr checks" << std::endl;
    std::cout << "5. Macro commands combine multiple operations" << std::endl;
    std::cout << "6. Adding new commands doesn't require changing RemoteControl" << std::endl;

    return 0;
}

/**
 * @brief Demonstrates basic command execution
 *
 * Shows how to:
 * - Create receivers (devices)
 * - Create commands bound to receivers
 * - Configure invoker (remote control)
 * - Execute commands via invoker
 */
void demonstrateBasicCommands() {
    std::cout << "--- Demonstration 1: Basic Command Execution ---" << std::endl;
    std::cout << std::endl;

    // Create receivers (devices)
    Light livingRoomLight("Living Room");
    Light kitchenLight("Kitchen");
    Stereo stereo("Living Room");

    // Create commands bound to receivers
    auto livingRoomLightOn = std::make_shared<LightOnCommand>(&livingRoomLight);
    auto livingRoomLightOff = std::make_shared<LightOffCommand>(&livingRoomLight);
    auto kitchenLightOn = std::make_shared<LightOnCommand>(&kitchenLight);
    auto kitchenLightOff = std::make_shared<LightOffCommand>(&kitchenLight);
    auto stereoOnWithCD = std::make_shared<StereoOnWithCDCommand>(&stereo);
    auto stereoOff = std::make_shared<StereoOffCommand>(&stereo);

    // Configure invoker (remote control)
    RemoteControl remote;
    remote.setCommand(0, livingRoomLightOn, livingRoomLightOff);
    remote.setCommand(1, kitchenLightOn, kitchenLightOff);
    remote.setCommand(2, stereoOnWithCD, stereoOff);

    // Display remote configuration
    std::cout << remote << std::endl;

    // Execute commands via remote control
    std::cout << "Pressing buttons..." << std::endl;
    std::cout << std::endl;

    std::cout << "Slot 0 ON:" << std::endl;
    remote.onButtonWasPushed(0);
    std::cout << std::endl;

    std::cout << "Slot 0 OFF:" << std::endl;
    remote.offButtonWasPushed(0);
    std::cout << std::endl;

    std::cout << "Slot 1 ON:" << std::endl;
    remote.onButtonWasPushed(1);
    std::cout << std::endl;

    std::cout << "Slot 1 OFF:" << std::endl;
    remote.offButtonWasPushed(1);
    std::cout << std::endl;

    std::cout << "Slot 2 ON:" << std::endl;
    remote.onButtonWasPushed(2);
    std::cout << std::endl;

    std::cout << "Slot 2 OFF:" << std::endl;
    remote.offButtonWasPushed(2);
    std::cout << std::endl;
}

/**
 * @brief Demonstrates undo functionality
 *
 * Shows how commands can reverse their operations.
 * This is one of the key benefits of the Command pattern.
 */
void demonstrateUndoFunctionality() {
    std::cout << "--- Demonstration 2: Undo Functionality ---" << std::endl;
    std::cout << std::endl;

    // Create receiver
    Light light("Bedroom");

    // Create commands
    auto lightOn = std::make_shared<LightOnCommand>(&light);
    auto lightOff = std::make_shared<LightOffCommand>(&light);

    // Configure remote
    RemoteControl remote;
    remote.setCommand(0, lightOn, lightOff);

    // Turn light on
    std::cout << "Turn light ON:" << std::endl;
    remote.onButtonWasPushed(0);
    std::cout << std::endl;

    // Undo (turns light off)
    std::cout << "Press UNDO (should turn light OFF):" << std::endl;
    remote.undoButtonWasPushed();
    std::cout << std::endl;

    // Turn light off
    std::cout << "Turn light OFF:" << std::endl;
    remote.offButtonWasPushed(0);
    std::cout << std::endl;

    // Undo (turns light on)
    std::cout << "Press UNDO (should turn light ON):" << std::endl;
    remote.undoButtonWasPushed();
    std::cout << std::endl;
}

/**
 * @brief Demonstrates macro commands (composite pattern)
 *
 * Shows how multiple commands can be combined into one macro command.
 * Useful for "scenes" like "Party Mode" or "Movie Mode".
 */
void demonstrateMacroCommands() {
    std::cout << "--- Demonstration 3: Macro Commands (Party Mode) ---" << std::endl;
    std::cout << std::endl;

    // Create receivers
    Light light1("Living Room");
    Light light2("Kitchen");
    Stereo stereo("Living Room");

    // Create individual commands
    auto light1On = std::make_shared<LightOnCommand>(&light1);
    auto light1Off = std::make_shared<LightOffCommand>(&light1);
    auto light2On = std::make_shared<LightOnCommand>(&light2);
    auto light2Off = std::make_shared<LightOffCommand>(&light2);
    auto stereoOn = std::make_shared<StereoOnWithCDCommand>(&stereo);
    auto stereoOff = std::make_shared<StereoOffCommand>(&stereo);

    // Create macro commands for "Party Mode"
    std::vector<std::shared_ptr<Command>> partyOn = {light1On, light2On, stereoOn};
    std::vector<std::shared_ptr<Command>> partyOff = {light1Off, light2Off, stereoOff};

    auto partyOnMacro = std::make_shared<MacroCommand>(partyOn);
    auto partyOffMacro = std::make_shared<MacroCommand>(partyOff);

    // Configure remote
    RemoteControl remote;
    remote.setCommand(0, partyOnMacro, partyOffMacro);

    // Execute party mode ON
    std::cout << "Activating PARTY MODE (macro command):" << std::endl;
    remote.onButtonWasPushed(0);
    std::cout << std::endl;

    // Undo party mode (turns everything off in reverse order)
    std::cout << "Press UNDO (should turn off everything in reverse order):" << std::endl;
    remote.undoButtonWasPushed();
    std::cout << std::endl;

    // Execute party mode OFF
    std::cout << "Deactivating PARTY MODE:" << std::endl;
    remote.offButtonWasPushed(0);
    std::cout << std::endl;
}
