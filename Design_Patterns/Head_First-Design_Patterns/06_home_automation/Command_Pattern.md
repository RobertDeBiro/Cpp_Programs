# Command Pattern - Comprehensive Analysis

## Table of Contents

1. [Pattern Overview](#pattern-overview)
2. [The Problem: Tight Coupling Between Requester and Action](#the-problem-tight-coupling-between-requester-and-action)
3. [Real-World Example: Robot Motion Control System](#real-world-example-robot-motion-control-system)
4. [Design Principles](#design-principles)
5. [The Solution: Command Pattern](#the-solution-command-pattern)
6. [Benefits and Trade-offs](#benefits-and-trade-offs)
7. [C++ Specific Considerations](#c-specific-considerations)
8. [Pattern Relationships](#pattern-relationships)

---

## Pattern Overview

**Command Pattern** encapsulates a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undoable operations.

**Key Intent:** Decouple the object that invokes the operation from the object that knows how to perform it.

**Also Known As:** Action, Transaction

---

## The Problem: Tight Coupling Between Requester and Action

### Bad Architecture Example: Hardcoded Remote Control

```cpp
// BAD: RemoteControl tightly coupled to specific device implementations
class RemoteControl {
private:
    Light* livingRoomLight;
    Stereo* stereo;
    GarageDoor* garageDoor;

public:
    void button1Pressed() {
        // PROBLEM 1: Invoker knows about specific receiver implementation
        livingRoomLight->on();
    }

    void button2Pressed() {
        stereo->on();
        stereo->setCD();
        stereo->setVolume(11);
    }

    void button3Pressed() {
        garageDoor->up();
    }

    // PROBLEM 2: Cannot undo operations
    // PROBLEM 3: Cannot queue or log commands
    // PROBLEM 4: Cannot support macro commands (multiple operations)
    // PROBLEM 5: Adding new device requires modifying RemoteControl class
};
```

### Pain Points

1. **Tight Coupling**
   - `RemoteControl` directly depends on `Light`, `Stereo`, `GarageDoor` classes
   - Every new device type requires modifying `RemoteControl`
   - Violates Open/Closed Principle

2. **No Undo/Redo Support**
   - Once action is performed, cannot reverse it
   - No history tracking
   - Cannot implement multi-level undo

3. **Cannot Parameterize Requests**
   - Cannot pass operations as parameters to methods
   - Cannot store operations in data structures (queues, logs)
   - Cannot dynamically assign buttons to different actions

4. **No Command Queuing**
   - Cannot schedule operations for later execution
   - Cannot implement job queues or thread pools
   - Cannot batch operations

5. **No Logging/Auditing**
   - Cannot log operations for replay
   - Cannot implement crash recovery
   - Cannot audit what actions were performed

6. **Violates Single Responsibility**
   - `RemoteControl` responsible for UI AND knowing how to control devices
   - Changes to device control logic require changing invoker

### Example of Cascading Problems

```cpp
// As system grows, this becomes unmaintainable:
class RemoteControl {
    void button1Pressed() {
        if (mode == NORMAL) {
            livingRoomLight->on();
        } else if (mode == PARTY) {
            livingRoomLight->on();
            stereo->on();
            stereo->setCD();
            stereo->setVolume(11);
            // ... 10 more operations
        } else if (mode == MOVIE) {
            livingRoomLight->dim(50);
            stereo->on();
            stereo->setDVD();
            // ... 10 more operations
        }
    }
    // This grows exponentially! 7 buttons × 5 modes × N devices = chaos
};
```

**Result:** A tangled mess of if-else logic, impossible to test, extend, or maintain.

---

## Real-World Example: Robot Motion Control System

### Scenario: Autonomous Mobile Robot

You are building a **warehouse robot** that navigates to pick and place items. The robot receives motion commands from:

- Manual operator (joystick)
- Path planning algorithm (autonomous navigation)
- Recovery system (undo failed operations)
- Script playback (replay recorded sequences)

Each command must:
- Be queueable (execute later when robot is ready)
- Support undo (revert position if operation fails)
- Be loggable (audit trail for debugging)
- Be composable (macro commands like "go to station 5 and pick item")

### Bad Architecture: Direct Robot Control

```cpp
// BAD: Controller tightly coupled to robot hardware
class RobotController {
private:
    MotorDriver* motors;
    GripperDriver* gripper;
    SensorArray* sensors;

public:
    void handleJoystickInput(JoystickEvent event) {
        // PROBLEM: Controller knows low-level hardware details
        if (event.button == FORWARD) {
            motors->setLeftSpeed(100);
            motors->setRightSpeed(100);
        } else if (event.button == TURN_LEFT) {
            motors->setLeftSpeed(50);
            motors->setRightSpeed(100);
        }
        // Cannot undo movements!
        // Cannot queue commands for autonomous mode!
        // Cannot log for crash recovery!
    }

    void autonomousNavigation() {
        // PROBLEM: Path planner duplicates control logic
        motors->setLeftSpeed(100);
        motors->setRightSpeed(100);
        // ... duplicate code from manual control
    }

    void executeRecovery() {
        // PROBLEM: No way to undo previous commands
        // Must manually reverse engineer what happened
    }
};
```

### Why This Fails in Production

1. **Cannot Switch Between Control Modes**
   - Manual, autonomous, and recovery modes all need same operations
   - Code duplication across all modes
   - Inconsistent behavior between modes

2. **No Undo for Failed Operations**
   - Robot picks wrong item → cannot undo pick operation
   - Robot detects obstacle mid-movement → cannot backtrack
   - Must manually reset robot position

3. **Cannot Queue Commands**
   - Path planner generates 50 movement commands
   - No way to queue them for sequential execution
   - Must execute synchronously (blocking)

4. **Cannot Log for Debugging**
   - Robot crashes → no record of what commands were issued
   - Cannot replay scenario to reproduce bug
   - No audit trail for safety-critical operations

5. **Testing is Impossible**
   - Cannot test controller logic without real hardware
   - Cannot inject test commands
   - Cannot verify command sequences

---

## Design Principles

### 1. Encapsulation (of Requests)

**Definition:** Encapsulate a request as an object.

**Before Command Pattern:**

```cpp
// Request is just a method call (not reified)
remoteControl.button1Pressed();  // Lost after execution
```

**After Command Pattern:**

```cpp
// Request is an object that can be stored, passed, queued, logged
std::unique_ptr<Command> cmd = std::make_unique<LightOnCommand>(light);
remoteControl.setCommand(0, std::move(cmd));  // Store for later
cmdQueue.push(cmd);  // Queue for batch execution
cmdLog.record(cmd);  // Log for audit trail
cmd->execute();      // Execute when ready
cmd->undo();         // Reverse the operation
```

**Key Insight:** By reifying requests as objects, they become first-class citizens that can be manipulated like any other object.

### 2. Separation of Concerns

**Definition:** Separate the object that invokes the operation from the object that knows how to perform it.

**Three Distinct Responsibilities:**

1. **Invoker** (RemoteControl): Knows WHEN to execute
2. **Command** (LightOnCommand): Knows WHAT to execute and HOW to undo
3. **Receiver** (Light): Knows HOW to perform the actual work

Each can change independently.

### 3. Open/Closed Principle

**Definition:** Open for extension, closed for modification.

- **Open:** Add new command types without changing invoker
- **Closed:** Invoker code never changes when adding new commands

```cpp
// Add new device type: NO changes to RemoteControl
class CeilingFanHighCommand : public Command {
    CeilingFan* fan;
public:
    void execute() override { fan->high(); }
    void undo() override { fan->off(); }
};

// RemoteControl code unchanged - it just calls execute()
```

### 4. Dependency Inversion

**Definition:** Depend on abstractions, not concrete classes.

```cpp
// Invoker depends only on Command interface
class RemoteControl {
    std::vector<std::unique_ptr<Command>> commands;  // Abstract

    void buttonPressed(int slot) {
        commands[slot]->execute();  // Polymorphic dispatch
    }
};
```

### 5. Single Responsibility Principle

- **RemoteControl:** Responsible for storing and invoking commands
- **Command:** Responsible for encapsulating request and knowing how to undo
- **Light:** Responsible for light-specific behavior

Each class has ONE reason to change.

---

## The Solution: Command Pattern

### Structure

```text
┌─────────────┐
│   Client    │  Creates ConcreteCommand, binds to Receiver
└──────┬──────┘
       │ creates
       ↓
┌─────────────────────┐        ┌──────────────┐
│ ConcreteCommand     │------->│  Receiver    │
│ (LightOnCommand)    │ binds  │  (Light)     │
├─────────────────────┤        ├──────────────┤
│ - receiver : Light* │        │ + on()       │
│ + execute()         │        │ + off()      │
│ + undo()            │        └──────────────┘
└─────────────────────┘
         △
         │ implements
┌────────┴────────┐
│ Command         │  ← Interface
├─────────────────┤
│ + execute() = 0 │
│ + undo() = 0    │
└─────────────────┘
         △
         │ uses
┌────────┴────────┐
│    Invoker      │  Asks command to execute
│ (RemoteControl) │
├─────────────────┤
│ - command       │
│ + buttonPressed │
└─────────────────┘
```

### Key Components

1. **Command (Interface)**
   - Declares `execute()` and `undo()` methods
   - All concrete commands implement this interface

2. **ConcreteCommand** (e.g., `LightOnCommand`, `StereoOnCommand`)
   - Implements `Command` interface
   - Binds a Receiver with an action
   - `execute()` invokes receiver's method
   - `undo()` reverses the action

3. **Receiver** (e.g., `Light`, `Stereo`)
   - Knows how to perform actual work
   - Has methods like `on()`, `off()`, `setVolume()`

4. **Invoker** (e.g., `RemoteControl`)
   - Holds references to Command objects
   - Calls `execute()` when action is needed
   - **Does NOT know about concrete commands or receivers**

5. **Client**
   - Creates ConcreteCommand objects
   - Binds commands to receivers
   - Configures invoker with commands

### How It Works

```cpp
// Client creates receiver
Light* light = new Light("Living Room");

// Client creates command and binds to receiver
Command* lightOn = new LightOnCommand(light);

// Client configures invoker
RemoteControl remote;
remote.setCommand(0, lightOn);

// User presses button
remote.buttonPressed(0);
//        ↓
//    remote calls: commands[0]->execute()
//        ↓
//    LightOnCommand::execute() calls: light->on()
//        ↓
//    Light turns on

// User presses undo
remote.undoButtonPressed();
//        ↓
//    remote calls: lastCommand->undo()
//        ↓
//    LightOnCommand::undo() calls: light->off()
//        ↓
//    Light turns off
```

**Critical Insight:** The invoker is completely decoupled from receivers. It only knows about the `Command` interface. Adding new devices or commands requires NO changes to the invoker.

---

## Benefits and Trade-offs

### Benefits

1. **Decouples Invoker from Receiver**
   - Invoker doesn't know about receiver classes
   - Can change receiver implementation without affecting invoker
   - Can swap receivers at runtime

2. **Commands are First-Class Objects**
   - Can be stored in data structures (arrays, vectors, queues)
   - Can be passed as parameters
   - Can be returned from functions
   - Can be logged, serialized, transmitted

3. **Undo/Redo Support**
   - Commands encapsulate enough state to reverse operations
   - Can maintain command history for multi-level undo
   - Essential for interactive applications

4. **Command Queuing**
   - Queue commands for later execution
   - Implement thread pools (worker threads execute commands from queue)
   - Schedule operations

5. **Logging and Crash Recovery**
   - Log executed commands to persistent storage
   - Replay commands to restore state after crash
   - Audit trail for debugging

6. **Macro Commands**
   - Combine multiple commands into one composite command
   - Execute batch operations atomically
   - Example: "Party mode" = turn on lights + stereo + set volume

7. **Testability**
   - Easy to test invoker with mock commands
   - Easy to test commands in isolation
   - Can verify command sequences

8. **Extensibility**
   - Add new command types without modifying existing code
   - Open/Closed Principle in action

### Trade-offs

1. **Increased Number of Classes**
   - Each operation requires a command class
   - Can lead to class proliferation
   - Mitigated by: Clear separation of concerns, easier maintenance

2. **Indirection**
   - Extra layer between invoker and receiver
   - Slightly more complex than direct method calls
   - Mitigated by: Benefits outweigh the cost in non-trivial systems

3. **Memory Overhead**
   - Each command is an object (heap allocation)
   - Undo history consumes memory
   - Mitigated by: Use smart pointers, limit undo history size

4. **Complexity for Simple Cases**
   - Overkill for simple one-off operations
   - Mitigated by: Use pattern only when benefits are needed

### When to Use Command Pattern

- ✅ Need to parameterize objects with operations (callbacks)
- ✅ Need to queue, schedule, or execute operations at different times
- ✅ Need to support undo/redo
- ✅ Need to log operations for auditing or crash recovery
- ✅ Need to support transactional behavior (execute/rollback)
- ✅ Need to decouple invoker from implementation details
- ❌ Simple one-off operations with no special requirements
- ❌ Performance-critical tight loops (use direct calls)

---

## C++ Specific Considerations

### 1. Smart Pointers for Automatic Memory Management

**Problem with Raw Pointers:**

```cpp
// DANGEROUS: Who owns the command? When is it deleted?
class RemoteControl {
    Command* commands[7];  // Manual memory management nightmare
};
```

**Solution: Use `std::unique_ptr` for exclusive ownership:**

```cpp
class RemoteControl {
private:
    std::array<std::unique_ptr<Command>, 7> onCommands;
    std::array<std::unique_ptr<Command>, 7> offCommands;
    std::unique_ptr<Command> undoCommand;  // Last executed command

public:
    void setCommand(int slot,
                   std::unique_ptr<Command> onCmd,
                   std::unique_ptr<Command> offCmd) {
        onCommands[slot] = std::move(onCmd);   // Transfer ownership
        offCommands[slot] = std::move(offCmd);
    }

    void onButtonWasPushed(int slot) {
        onCommands[slot]->execute();
        undoCommand = onCommands[slot]->clone();  // Clone for undo
    }
};
```

**Why `unique_ptr`?**

- **Exclusive ownership:** RemoteControl owns the commands
- **RAII:** Automatic cleanup when RemoteControl is destroyed
- **Move semantics:** Efficient transfer of ownership
- **No manual delete:** Prevents memory leaks

### 2. Virtual Destructors in Polymorphic Hierarchies

```cpp
class Command {
public:
    virtual ~Command() = default;  // ESSENTIAL for polymorphic deletion
    virtual void execute() = 0;
    virtual void undo() = 0;
};
```

**Why virtual destructor?**

```cpp
std::unique_ptr<Command> cmd = std::make_unique<LightOnCommand>(light);
// When cmd is destroyed, WITHOUT virtual destructor:
//   → Only ~Command() is called (memory leak if derived class has resources)
// WITH virtual destructor:
//   → ~LightOnCommand() called, then ~Command() (correct cleanup)
```

### 3. Pure Virtual Functions for Abstract Interface

```cpp
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;  // Pure virtual - must be overridden
    virtual void undo() = 0;     // Pure virtual - must be overridden

    // Optional: Clone for command history
    virtual std::unique_ptr<Command> clone() const = 0;
};
```

### 4. Null Object Pattern to Avoid Null Checks

```cpp
// Instead of checking for nullptr everywhere
if (commands[slot] != nullptr) {
    commands[slot]->execute();
}

// Use Null Object Pattern
class NoCommand : public Command {
public:
    void execute() override {}  // Do nothing
    void undo() override {}     // Do nothing
};

// Initialize with NoCommand
RemoteControl::RemoteControl() {
    auto noCommand = std::make_shared<NoCommand>();
    for (int i = 0; i < 7; ++i) {
        onCommands[i] = noCommand;   // Share null object
        offCommands[i] = noCommand;
    }
}

// Now can always call execute() without null check
void onButtonWasPushed(int slot) {
    onCommands[slot]->execute();  // Safe - always valid
}
```

### 5. std::function for Lightweight Commands (Alternative)

For simple cases, can use `std::function` instead of command classes:

```cpp
class RemoteControl {
private:
    std::array<std::function<void()>, 7> onCommands;
    std::array<std::function<void()>, 7> offCommands;

public:
    void setCommand(int slot,
                   std::function<void()> onCmd,
                   std::function<void()> offCmd) {
        onCommands[slot] = onCmd;
        offCommands[slot] = offCmd;
    }
};

// Usage
Light light("Living Room");
remote.setCommand(0,
    [&light]() { light.on(); },   // Lambda as command
    [&light]() { light.off(); }
);
```

**Trade-off:** `std::function` is simpler but doesn't support undo easily.

### 6. Command History with Deque

```cpp
class RemoteControlWithHistory {
private:
    std::deque<std::unique_ptr<Command>> history;
    const size_t MAX_HISTORY = 10;

public:
    void executeCommand(std::unique_ptr<Command> cmd) {
        cmd->execute();

        // Add to history
        history.push_back(std::move(cmd));

        // Limit history size
        if (history.size() > MAX_HISTORY) {
            history.pop_front();
        }
    }

    void undo() {
        if (!history.empty()) {
            history.back()->undo();
            history.pop_back();
        }
    }
};
```

### 7. Const Correctness

```cpp
class Command {
public:
    virtual void execute() = 0;      // Non-const: may modify receiver
    virtual void undo() = 0;         // Non-const: may modify receiver

    // Query methods should be const
    virtual std::string getName() const = 0;
};
```

### 8. Modern C++20 Features

```cpp
// Concept for Command interface (C++20)
template<typename T>
concept CommandType = requires(T cmd) {
    { cmd.execute() } -> std::same_as<void>;
    { cmd.undo() } -> std::same_as<void>;
};

// Constrain template to Command types
template<CommandType T>
void executeCommand(T& cmd) {
    cmd.execute();
}
```

---

## Pattern Relationships

### Command vs Other Patterns

1. **Command + Memento**
   - Command: Encapsulates request
   - Memento: Encapsulates state for undo
   - Combination: Command stores Memento for complex undo
   ```cpp
   class MoveCommand : public Command {
       Robot* robot;
       Memento previousState;  // Captured before execute()
   public:
       void execute() override {
           previousState = robot->saveState();
           robot->moveForward();
       }
       void undo() override {
           robot->restoreState(previousState);
       }
   };
   ```

2. **Command + Composite (Macro Commands)**
   - Composite: Treat individual commands and groups uniformly
   ```cpp
   class MacroCommand : public Command {
       std::vector<std::unique_ptr<Command>> commands;
   public:
       void add(std::unique_ptr<Command> cmd) {
           commands.push_back(std::move(cmd));
       }
       void execute() override {
           for (auto& cmd : commands) cmd->execute();
       }
       void undo() override {
           for (auto it = commands.rbegin(); it != commands.rend(); ++it) {
               (*it)->undo();
           }
       }
   };
   ```

3. **Command + Strategy**
   - Both encapsulate algorithms/operations
   - Strategy: Interchangeable algorithms for same problem
   - Command: Encapsulates diverse operations, supports undo/queue
   - Strategy focuses on HOW, Command focuses on WHAT and WHEN

4. **Command + Observer**
   - Can notify observers when command is executed
   ```cpp
   class Command {
       std::vector<CommandObserver*> observers;
   public:
       void execute() {
           doExecute();
           notifyObservers();
       }
   };
   ```

5. **Command + Chain of Responsibility**
   - Chain: Pass command along chain until handler found
   - Useful for event handling systems

### Common Combinations in Robotics Example

```cpp
// Command + Memento for robot motion undo
class RobotMoveCommand : public Command {
    Robot* robot;
    RobotState previousState;  // Memento
public:
    void execute() override {
        previousState = robot->getState();
        robot->move(dx, dy);
    }
    void undo() override {
        robot->setState(previousState);
    }
};

// Macro Command for composite operations
class PickAndPlaceSequence : public MacroCommand {
public:
    PickAndPlaceSequence(Robot* robot, Item* item, Location* dest) {
        add(std::make_unique<MoveToCommand>(robot, item->location));
        add(std::make_unique<GripperCloseCommand>(robot));
        add(std::make_unique<LiftCommand>(robot, 50));
        add(std::make_unique<MoveToCommand>(robot, dest));
        add(std::make_unique<LowerCommand>(robot, 0));
        add(std::make_unique<GripperOpenCommand>(robot));
    }
};

// Command Queue for autonomous execution
class AutonomousController {
    std::queue<std::unique_ptr<Command>> commandQueue;
public:
    void scheduleCommand(std::unique_ptr<Command> cmd) {
        commandQueue.push(std::move(cmd));
    }
    void executeNext() {
        if (!commandQueue.empty()) {
            auto cmd = std::move(commandQueue.front());
            commandQueue.pop();
            cmd->execute();
        }
    }
};
```

---

## Summary: The Power of Command Pattern

**Before Command Pattern:**

- Invoker tightly coupled to receiver implementations
- Cannot undo operations
- Cannot queue, log, or parameterize requests
- Difficult to test
- Adding new operations requires modifying invoker

**After Command Pattern:**

- ✅ **Decoupling:** Invoker knows only Command interface
- ✅ **Undo/Redo:** Commands encapsulate state for reversal
- ✅ **Queueing:** Commands are objects that can be stored/scheduled
- ✅ **Logging:** Record commands for crash recovery/audit
- ✅ **Macro Commands:** Combine operations into composite commands
- ✅ **Testability:** Easy to test with mock commands
- ✅ **Extensibility:** Add commands without modifying invoker

**Architectural Thinking:**

> When you find yourself writing code where one object needs to invoke operations on another but shouldn't know the details, you need the Command Pattern. By reifying requests as objects, you transform operations into first-class citizens that can be stored, passed, queued, logged, and undone. This is the essence of **encapsulating requests** and **decoupling invokers from receivers**.

**Real-World Impact:**

In the robotics example, Command Pattern enables:
- Manual, autonomous, and recovery modes share same command infrastructure
- Failed operations can be undone (critical for safety)
- Path planner generates command sequences that execute asynchronously
- All operations logged for debugging and safety auditing
- Test suite validates commands without real hardware

This transforms a rigid, error-prone system into a flexible, testable, maintainable architecture.

---

## References

- **Design Principles:** Encapsulation (of requests), Separation of Concerns, Open/Closed, Dependency Inversion, Single Responsibility
- **C++ Features:** Smart pointers (`unique_ptr`), virtual destructors, RAII, `std::function`, lambdas
- **Related Patterns:** Memento, Composite (Macro Commands), Strategy, Observer, Chain of Responsibility
- **Real-World Application:** Robot control, transaction systems, GUI undo/redo, job scheduling, command-line interpreters

