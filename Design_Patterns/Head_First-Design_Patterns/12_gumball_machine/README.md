# State Pattern - Gumball Machine

## Overview

This project demonstrates the **State Pattern**, a behavioral design pattern that allows an object to alter its behavior when its internal state changes. The object will appear to change its class.

The example implements a gumball vending machine that transitions through multiple states based on user actions and internal conditions.

## Pattern Definition

**State Pattern** allows an object to alter its behavior when its internal state changes. The object will appear to change its class.

**Key Components**:
- **Context (GumballMachine)**: Maintains a reference to the current state and delegates state-dependent operations
- **State (Interface)**: Defines the interface for all state-dependent operations
- **ConcreteStates**: Implement specific behavior for each state (NoQuarterState, HasQuarterState, SoldState, SoldOutState, WinnerState)

## The Problem: Giant Conditionals

### Without State Pattern (Anti-Pattern)

```cpp
class GumballMachine {
    const int SOLD_OUT = 0;
    const int NO_QUARTER = 1;
    const int HAS_QUARTER = 2;
    const int SOLD = 3;
    int state = SOLD_OUT;

    void insertQuarter() {
        if (state == HAS_QUARTER) {
            std::cout << "You can't insert another quarter\n";
        } else if (state == NO_QUARTER) {
            state = HAS_QUARTER;
            std::cout << "You inserted a quarter\n";
        } else if (state == SOLD_OUT) {
            std::cout << "You can't insert a quarter, the machine is sold out\n";
        } else if (state == SOLD) {
            std::cout << "Please wait, we're already giving you a gumball\n";
        }
    }

    // Every method has similar conditional chains!
    void ejectQuarter() { /* 4 if-else branches */ }
    void turnCrank() { /* 4 if-else branches */ }
    void dispense() { /* 4 if-else branches */ }
};
```

### Problems with This Approach

1. **Not Extensible**: Adding a new state (e.g., WINNER) requires modifying EVERY method
2. **Violates Open/Closed Principle**: Can't extend without modifying existing code
3. **Code Duplication**: Same state checks repeated in every method
4. **Hidden State Transitions**: State changes buried in conditional blocks
5. **Difficult to Test**: Each method has multiple code paths
6. **Poor Encapsulation**: All state logic in one monolithic class

## The Solution: State Pattern

### With State Pattern

```cpp
// State Interface
class State {
public:
    virtual void insertQuarter(GumballMachine* machine) = 0;
    virtual void ejectQuarter(GumballMachine* machine) = 0;
    virtual void turnCrank(GumballMachine* machine) = 0;
    virtual void dispense(GumballMachine* machine) = 0;
};

// Concrete State Example
class NoQuarterState : public State {
    void insertQuarter(GumballMachine* machine) override {
        std::cout << "You inserted a quarter\n";
        machine->setState(machine->getHasQuarterState());
    }
    // ... other methods
};

// Context
class GumballMachine {
    State* state;
public:
    void insertQuarter() {
        state->insertQuarter(this);  // Just delegate!
    }
};
```

## State Machine

### States

1. **NO_QUARTER**: Machine is waiting for customer to insert quarter
2. **HAS_QUARTER**: Quarter inserted, waiting for crank turn
3. **SOLD**: Dispensing a gumball
4. **SOLD_OUT**: No gumballs available
5. **WINNER**: Special state - dispense 2 gumballs (1 in 10 chance)

### State Transitions

```
SOLD_OUT ←──────────────────────────────┐
    ↑                                    │
    │ refill()                           │ count == 0
    ↓                                    │
NO_QUARTER ←─────────────────┐          │
    ↓                         │          │
    │ insertQuarter()         │          │
    ↓                         │          │
HAS_QUARTER                   │          │
    ↓                         │          │
    │ turnCrank()             │          │
    ↓                         │          │
    ├──→ SOLD (90%)    ──────┘          │
    │       ↓                            │
    │       dispense() (count > 0)      │
    │                                    │
    └──→ WINNER (10%) ──────────────────┘
            ↓
            dispense() x2
```

### Actions per State

| State | insertQuarter() | ejectQuarter() | turnCrank() | dispense() |
|-------|----------------|---------------|-------------|------------|
| **NO_QUARTER** | → HAS_QUARTER | Error message | Error message | Error message |
| **HAS_QUARTER** | Error message | → NO_QUARTER | → SOLD/WINNER | Error message |
| **SOLD** | Error message | Error message | Error message | Release ball → NO_QUARTER/SOLD_OUT |
| **SOLD_OUT** | Error message | Error message | Error message | Error message |
| **WINNER** | Error message | Error message | Error message | Release 2 balls → NO_QUARTER/SOLD_OUT |

## Benefits of State Pattern

### 1. Eliminates Conditional Logic

**Before**:
```cpp
void insertQuarter() {
    if (state == HAS_QUARTER) { /* ... */ }
    else if (state == NO_QUARTER) { /* ... */ }
    else if (state == SOLD_OUT) { /* ... */ }
    else if (state == SOLD) { /* ... */ }
}
```

**After**:
```cpp
void insertQuarter() {
    state->insertQuarter(this);  // Clean delegation!
}
```

### 2. Localizes State-Specific Behavior

All behavior for a particular state is encapsulated in one class:

```cpp
class NoQuarterState : public State {
    // ALL NoQuarter behavior in one place
    void insertQuarter(GumballMachine* machine) override;
    void ejectQuarter(GumballMachine* machine) override;
    void turnCrank(GumballMachine* machine) override;
    void dispense(GumballMachine* machine) override;
};
```

### 3. Makes State Transitions Explicit

```cpp
// Clear transition
machine->setState(machine->getHasQuarterState());

// vs hidden in conditionals:
// if (state == NO_QUARTER) { state = HAS_QUARTER; }
```

### 4. Open/Closed Principle

Adding the WINNER state required:
- Creating ONE new class (WinnerState)
- Modifying ONE method in ONE existing class (HasQuarterState::turnCrank)
- NO changes to other state classes

### 5. Testable

Each state can be tested independently:

```cpp
TEST(NoQuarterState, InsertQuarterTransitionsToHasQuarter) {
    GumballMachine machine(5);
    NoQuarterState state;
    state.insertQuarter(&machine);
    EXPECT_EQ(machine.getCurrentState(), machine.getHasQuarterState());
}
```

## State vs Strategy Pattern

### Structural Similarity

Both patterns have nearly identical structure, but different intent:

```cpp
// Both have a context with a reference to an interface
class Context {
    Interface* object;
};
```

### Key Differences

| Aspect | State Pattern | Strategy Pattern |
|--------|---------------|------------------|
| **Intent** | Alter behavior when state changes | Choose algorithm at runtime |
| **Who decides** | Context or states transition | Client chooses strategy |
| **Transitions** | States transition to other states | No transitions between strategies |
| **State awareness** | States may know about other states | Strategies are independent |
| **Purpose** | State-dependent behavior | Alternative algorithms |
| **Example** | TCP connection (CLOSED→LISTEN→ESTABLISHED) | Sorting (QuickSort, MergeSort) |

### Conceptual Difference

**State Pattern**: "The object behaves differently in different states, and transitions between those states."

```cpp
TcpConnection conn;
conn.open();   // CLOSED → SYN_SENT (automatic transition)
// State changes automatically based on network events
```

**Strategy Pattern**: "Here are different ways to accomplish the same goal. Pick one."

```cpp
Sorter sorter;
sorter.setStrategy(new QuickSort());  // Client chooses
sorter.sort(data);
sorter.setStrategy(new MergeSort());  // Client chooses different strategy
```

## C++ Implementation Considerations

### 1. State Ownership

This implementation uses **Context owns all states**:

```cpp
class GumballMachine {
    std::unique_ptr<State> soldOutState;    // Owned
    std::unique_ptr<State> noQuarterState;  // Owned
    std::unique_ptr<State> hasQuarterState; // Owned
    std::unique_ptr<State> soldState;       // Owned
    std::unique_ptr<State> winnerState;     // Owned

    State* state;  // Non-owning pointer to current state
};
```

**Advantages**:
- Simple: All states created at construction
- Fast: No allocation during transitions
- Safe: No dangling pointers

**When to use**: States are stateless or nearly stateless

### 2. Forward Declarations

Avoid circular dependencies:

```cpp
// State.h
class GumballMachine;  // Forward declaration

class State {
    virtual void insertQuarter(GumballMachine* machine) = 0;
};
```

### 3. Unused Parameters

Use `[[maybe_unused]]` for parameters required by interface but not used in implementation:

```cpp
void NoQuarterState::ejectQuarter([[maybe_unused]] GumballMachine* machine) {
    std::cout << "You haven't inserted a quarter\n";
    // machine not needed here, but required by State interface
}
```

### 4. Virtual Dispatch Performance

Virtual function calls are **not** a performance concern:
- Modern CPUs optimize virtual dispatch very well
- Often faster than long conditional chains (better branch prediction)

## Real-World Applications

### 1. Network Protocol Stacks

TCP connection states: CLOSED, LISTEN, SYN_SENT, ESTABLISHED, FIN_WAIT, etc.

### 2. Document Workflow

Document lifecycle: DRAFT → IN_REVIEW → APPROVED → PUBLISHED → ARCHIVED

### 3. Game Character AI

Character states: IDLE, PATROLLING, CHASING, ATTACKING, FLEEING

### 4. Media Players

Player states: STOPPED, PLAYING, PAUSED, BUFFERING

### 5. Order Processing

Order states: PENDING, PROCESSING, SHIPPED, DELIVERED, CANCELLED

### 6. Elevator Control

Elevator states: IDLE, MOVING_UP, MOVING_DOWN, DOOR_OPENING, DOOR_CLOSING

## Project Structure

```
12_gumball_machine/
├── CMakeLists.txt              # Build configuration
├── main.cpp                    # Demonstration program
├── inc/                        # Header files
│   ├── State.h                 # State interface
│   ├── GumballMachine.h        # Context class
│   ├── NoQuarterState.h        # Concrete state
│   ├── HasQuarterState.h       # Concrete state
│   ├── SoldState.h             # Concrete state
│   ├── SoldOutState.h          # Concrete state
│   └── WinnerState.h           # Concrete state (extension)
├── src/                        # Implementation files
│   ├── GumballMachine.cpp
│   ├── NoQuarterState.cpp
│   ├── HasQuarterState.cpp
│   ├── SoldState.cpp
│   ├── SoldOutState.cpp
│   └── WinnerState.cpp
├── scripts/                    # Build scripts
│   ├── conf.sh                 # Configure CMake
│   ├── build.sh                # Build project
│   ├── run.sh                  # Run executable
│   └── all.sh                  # Run all scripts
├── UML/
│   └── diagram.puml            # PlantUML class diagram
├── out/build/                  # Build output
├── State_Pattern.md         # Comprehensive analysis
└── README.md                   # This file
```

## Building and Running

### Prerequisites

- C++20 compatible compiler (GCC 11+, Clang 12+)
- CMake 3.20 or higher

### Quick Start

Run all steps (configure, build, and run):

```bash
./scripts/all.sh
```

### Step by Step

1. **Configure CMake**:
   ```bash
   ./scripts/conf.sh
   ```

2. **Build the project**:
   ```bash
   ./scripts/build.sh
   ```

3. **Run the demo**:
   ```bash
   ./scripts/run.sh
   ```

## Example Output

```
╔════════════════════════════════════════════════════════════╗
║         STATE PATTERN DEMONSTRATION                        ║
║         Gumball Machine Example                            ║
╚════════════════════════════════════════════════════════════╝

TEST 1: Basic Operation - Insert Quarter and Get Gumball
============================================================

>> Inserting quarter...
You inserted a quarter

>> Turning crank...
You turned...
A gumball comes rolling out the slot...

Inventory: 4 gumballs
Machine is waiting for quarter
```

## Design Principles Demonstrated

1. **Open/Closed Principle**: Open for extension (new states), closed for modification
2. **Single Responsibility**: Each state class has one reason to change
3. **Encapsulate What Varies**: State-specific behavior is encapsulated
4. **Favor Composition Over Inheritance**: Context HAS-A state
5. **Dependency Inversion**: Depend on State abstraction, not concrete states

## Key Takeaways

1. State Pattern eliminates conditional logic by encapsulating state-specific behavior into separate objects
2. Each state becomes a separate class implementing the State interface
3. Context delegates to the current state object instead of using conditionals
4. State transitions become explicit method calls instead of hidden variable assignments
5. Adding new states doesn't require modifying existing state classes
6. State Pattern is perfect for state machines with complex transitions
7. Different from Strategy Pattern: states transition automatically vs client choosing strategies

## Further Reading

- **Gang of Four**: Design Patterns - State Pattern (page 305)
- **Head First Design Patterns**: Chapter 10 - State Pattern
- **Martin Fowler**: Refactoring - Replace Conditional with Polymorphism
- **Robert C. Martin**: Clean Code - Objects and Data Structures
- **RFC 793**: Transmission Control Protocol (real-world state machine example)

## License

This is an educational implementation based on the Head First Design Patterns book.

## Author

Converted to modern C++20 with SonarQube compliance.
