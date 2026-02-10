# Command Pattern - Home Automation Remote Control

## Overview

Demonstration of the **Command Pattern** using a home automation remote control system. Shows how to encapsulate requests as objects, enabling parameterization of clients with different requests, queueing of requests, logging of requests, and support for undoable operations.

## Key Concepts

- **Encapsulation of Requests:** Commands are objects, not just method calls
- **Decoupling:** Invoker doesn't know about receiver implementations
- **Undo/Redo:** Commands know how to reverse their operations
- **Macro Commands:** Combine multiple commands into one composite command
- **Null Object Pattern:** NoCommand eliminates nullptr checks
- **First-Class Objects:** Commands can be stored, queued, logged, passed as parameters

## Project Structure

```text
06_home_automation/
├── CMakeLists.txt              # Build configuration
├── main.cpp                    # Main program entry point
├── inc/                        # Header files
│   ├── Command.h               # Command interface
│   ├── LightOnCommand.h        # Concrete command (light on)
│   ├── LightOffCommand.h       # Concrete command (light off)
│   ├── StereoOnWithCDCommand.h # Concrete command (stereo on)
│   ├── StereoOffCommand.h      # Concrete command (stereo off)
│   ├── NoCommand.h             # Null object pattern
│   ├── MacroCommand.h          # Composite command
│   ├── RemoteControl.h         # Invoker (with undo support)
│   ├── Light.h                 # Receiver (light device)
│   └── Stereo.h                # Receiver (stereo device)
├── src/                        # Source files (empty for header-only implementation)
├── out/
│   └── build/                  # Build output directory
├── scripts/                    # Build and run scripts
│   ├── conf.sh                # Configure CMake
│   ├── build.sh               # Build project
│   ├── run.sh                 # Run executable
│   └── all.sh                 # Run all steps (configure + build + run)
├── UML/                        # UML diagrams
│   └── diagram.puml
├── Command_Pattern.md         # Comprehensive pattern analysis
└── README.md
```

## Building and Running

### Option 1: Using the all-in-one script (Recommended)

```bash
cd scripts
./all.sh
```

This will configure, build, and run the project in one step.

### Option 2: Step-by-step

```bash
cd scripts
./conf.sh   # Configure CMake
./build.sh  # Build project
./run.sh    # Run executable
```

### Option 3: Manual CMake

```bash
cmake -S . -B out/build
cd out/build
make
./home_automation
```

## Expected Output

```text
=== Command Pattern - Home Automation Remote Control ===

--- Demonstration 1: Basic Command Execution ---

----- Remote Control -----
[slot 0] LightOnCommand     LightOffCommand
[slot 1] LightOnCommand     LightOffCommand
[slot 2] StereoOnWithCDCommand     StereoOffCommand
[slot 3] NoCommand     NoCommand
[slot 4] NoCommand     NoCommand
[slot 5] NoCommand     NoCommand
[slot 6] NoCommand     NoCommand
[undo] NoCommand

Pressing buttons...

Slot 0 ON:
Living Room light is on

Slot 0 OFF:
Living Room light is off

[... more operations ...]

--- Demonstration 2: Undo Functionality ---

Turn light ON:
Bedroom light is on

Press UNDO (should turn light OFF):
Bedroom light is off

--- Demonstration 3: Macro Commands (Party Mode) ---

Activating PARTY MODE (macro command):
Living Room light is on
Kitchen light is on
Living Room stereo is on
Living Room stereo is set for CD input
Living Room stereo volume set to 11

Press UNDO (should turn off everything in reverse order):
Living Room stereo is off
Kitchen light is off
Living Room light is off

=== Demonstration Complete ===
```

## Files

### Command Hierarchy (in `inc/`)

**Command Interface:**

- `Command.h` - Declares `execute()` and `undo()` methods

**Concrete Commands:**

- `LightOnCommand.h` - Turns light on, undo turns it off
- `LightOffCommand.h` - Turns light off, undo turns it on
- `StereoOnWithCDCommand.h` - Turns stereo on with CD, sets volume
- `StereoOffCommand.h` - Turns stereo off

**Special Commands:**

- `NoCommand.h` - Null Object pattern (does nothing)
- `MacroCommand.h` - Composite pattern (executes multiple commands)

### Receivers (in `inc/`)

- `Light.h` - Light device with `on()` and `off()` methods
- `Stereo.h` - Stereo device with `on()`, `off()`, `setCD()`, `setVolume()` methods

### Invoker (in `inc/`)

- `RemoteControl.h` - Holds commands, invokes them, supports undo

### Client

- `main.cpp` - Creates receivers, commands, configures remote, demonstrates pattern

## Design Highlights

### Modern C++ Features Used

- **Smart Pointers** (`std::shared_ptr`) - Shared ownership of commands in remote control
- **RAII** - Automatic cleanup of command objects
- **Virtual Destructors** - Proper cleanup in polymorphic hierarchies
- **Pure Virtual Functions** - Enforce implementation of `execute()` and `undo()`
- **Const Correctness** - Methods marked `const` where appropriate
- **STL Containers** - `std::array` for command storage, `std::vector` for macro commands
- **RTTI** - `typeid` for displaying command class names

### Why `std::shared_ptr` for Commands?

Commands need **shared ownership** in this implementation:

- Remote control holds commands in slots
- `undoCommand` may reference same command object
- Macro commands contain references to other commands
- Shared ownership prevents premature deletion

Alternative: `std::unique_ptr` + clone pattern for exclusive ownership

### Command Pattern in Action

```cpp
// 1. Client creates receivers
Light light("Living Room");
Stereo stereo("Living Room");

// 2. Client creates commands and binds to receivers
auto lightOn = std::make_shared<LightOnCommand>(&light);
auto stereoOn = std::make_shared<StereoOnWithCDCommand>(&stereo);

// 3. Client configures invoker
RemoteControl remote;
remote.setCommand(0, lightOn, lightOff);

// 4. User presses button - Invoker calls execute()
remote.onButtonWasPushed(0);
//        ↓
//    Calls: commands[0]->execute()
//        ↓
//    LightOnCommand::execute() calls: light->on()
//        ↓
//    Light turns on

// 5. User presses undo - Invoker calls undo()
remote.undoButtonWasPushed();
//        ↓
//    Calls: undoCommand->undo()
//        ↓
//    LightOnCommand::undo() calls: light->off()
//        ↓
//    Light turns off
```

**Critical Insight:** RemoteControl only knows about the `Command` interface. It has NO knowledge of `Light`, `Stereo`, or any other receiver classes. This is complete decoupling.

## Pattern Benefits Demonstrated

1. **Decoupling:** Invoker completely decoupled from receiver implementations
2. **Parameterization:** Buttons can be dynamically assigned different commands
3. **Undo/Redo:** Commands encapsulate state needed to reverse operations
4. **Queuing:** Commands are objects that can be stored in queues (not shown, but possible)
5. **Logging:** Commands can be logged for crash recovery or auditing (not shown, but possible)
6. **Macro Commands:** Multiple operations combined into one command (Party Mode example)
7. **Null Object:** NoCommand eliminates nullptr checks
8. **Testability:** Easy to test invoker with mock commands

## Architecture

```text
Command (Interface)
├── execute() : void
└── undo() : void

Concrete Commands (LightOnCommand, StereoOnCommand, etc.)
├── Bind to a Receiver (Light, Stereo)
├── execute() invokes receiver's method
└── undo() reverses the operation

Invoker (RemoteControl)
├── Holds Command objects in slots
├── Calls execute() when button pressed
├── Calls undo() when undo button pressed
└── Depends ONLY on Command interface

Receivers (Light, Stereo)
├── Know HOW to perform actual work
└── Independent of Command pattern
```

## Key Command Pattern Principles

1. **Commands are First-Class Objects** - Can be stored, passed, queued, logged
2. **Invoker Decoupled from Receiver** - Invoker knows nothing about receiver classes
3. **Support for Undo** - Commands encapsulate enough state to reverse operations
4. **Composite Commands** - MacroCommand combines multiple commands
5. **Null Object Pattern** - NoCommand provides safe default behavior
6. **Open/Closed Principle** - Add new commands without modifying invoker

## Comparison: Before vs After

| Aspect | Hardcoded Coupling (Before) | Command Pattern (After) |
|--------|----------------------------|-------------------------|
| **Invoker-Receiver** | Directly coupled | Decoupled via Command interface |
| **Undo** | Not supported | Built-in via `undo()` method |
| **Parameterization** | Fixed buttons | Dynamically assignable |
| **Queuing** | Not possible | Commands are objects, queueable |
| **Testing** | Requires real devices | Can use mock commands |
| **Extensibility** | Modify invoker for new devices | Add new command class only |

## Real-World Applications

### Robot Motion Control (See Command_Pattern.md)

```cpp
// Command Pattern for warehouse robot
class RobotMoveCommand : public Command {
    Robot* robot;
    Position previousPos;  // For undo
    int dx, dy;
public:
    void execute() override {
        previousPos = robot->getPosition();
        robot->move(dx, dy);
    }
    void undo() override {
        robot->setPosition(previousPos);
    }
};

// Usage
RobotController controller;
controller.scheduleCommand(std::make_unique<MoveCommand>(robot, 10, 0));
controller.scheduleCommand(std::make_unique<RotateCommand>(robot, 90));
controller.scheduleCommand(std::make_unique<GripperCloseCommand>(robot));

// Execute queued commands
controller.executeNext();  // Move
controller.executeNext();  // Rotate
controller.executeNext();  // Close gripper

// Undo if obstacle detected
controller.undo();  // Open gripper
controller.undo();  // Rotate back
controller.undo();  // Move back
```

**Benefits:**

- Manual, autonomous, and recovery modes share same command infrastructure
- Failed operations can be undone (critical for safety)
- Path planner generates command sequences that execute asynchronously
- All operations logged for debugging and safety auditing

### GUI Undo/Redo

Text editors, graphics programs, IDEs all use Command Pattern for undo/redo stacks.

### Transaction Systems

Database transactions, distributed systems use Command Pattern for rollback.

### Job Scheduling

Thread pools, task schedulers use Command Pattern to queue work items.

## Pattern Relationships

### Command + Composite (MacroCommand)

MacroCommand demonstrates the Composite pattern - treating individual commands and groups of commands uniformly.

### Command + Memento

For complex undo, commands can store Memento objects capturing receiver state.

### Command + Strategy

Both encapsulate algorithms, but:
- **Strategy:** Interchangeable algorithms for same problem
- **Command:** Encapsulate diverse operations, support undo/queue

### Command + Observer

Observers can be notified when commands execute, enabling event-driven architectures.

## Further Reading

See [Command_Pattern.md](Command_Pattern.md) for detailed architectural analysis, including:

- Problem analysis (tight coupling, no undo, no queuing)
- Real-world robotics example (warehouse robot motion control with undo)
- Design principles explained (Encapsulation of requests, Separation of concerns, Open/Closed, Dependency Inversion)
- Benefits, trade-offs, and when to use Command Pattern
- C++ specific considerations (smart pointers, virtual destructors, Null Object pattern, std::function alternative)
- Pattern relationships (Memento, Composite, Strategy, Observer, Chain of Responsibility)

## Summary

The Command Pattern transforms operations into objects, enabling:

- ✅ **Decoupling:** Invoker independent of receiver implementations
- ✅ **Undo/Redo:** Commands know how to reverse operations
- ✅ **Queuing:** Commands can be stored and executed later
- ✅ **Logging:** Commands can be logged for audit/recovery
- ✅ **Macro Commands:** Combine multiple operations
- ✅ **Extensibility:** Add commands without modifying invoker

**When to use:** Callbacks, undo/redo, job scheduling, transaction systems, GUI actions, robot control, any scenario where requests need to be parameterized, queued, logged, or undone.
