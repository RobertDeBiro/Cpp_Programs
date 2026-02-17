# State Pattern - Comprehensive Analysis

---

## Overview

The **State Pattern** is a behavioral pattern that allows an object to alter its behavior when its internal state changes. The object will appear to change its class. This pattern is essential for managing complex state-dependent behavior without resorting to massive conditional statements.

**The Core Insight**: Instead of using giant if-else or switch statements to handle state-dependent behavior, we encapsulate each state's behavior into separate state objects. The context object delegates to its current state object, which handles the behavior appropriately.

**The Architectural Shift**: From "checking state and branching" to "delegating to state objects that know how to behave."

---

## Pattern Definition

**State Pattern** allows an object to alter its behavior when its internal state changes. The object will appear to change its class.

**Key Intent**: Encapsulate state-specific behavior and delegate responsibilities to the current state object.

**Also Known As**: Objects for States

**Core Concept**: The State Pattern encapsulates the states of an object into separate state classes. Each state class implements the behavior appropriate for that state. The context object maintains a reference to the current state and delegates state-dependent operations to it.

---

## The Problem: Giant Conditional State Machines

### The Pain of Procedural State Management

Before understanding the State Pattern, let's experience the pain of managing states without it. Consider a gumball vending machine with these states:

- **SOLD_OUT**: No gumballs available
- **NO_QUARTER**: Waiting for customer to insert quarter
- **HAS_QUARTER**: Quarter inserted, waiting for crank turn
- **SOLD**: Dispensing gumball

And these actions:

- `insertQuarter()`: Customer inserts a quarter
- `ejectQuarter()`: Customer requests refund
- `turnCrank()`: Customer turns the crank
- `dispense()`: Machine dispenses gumball

### The "Bad" Implementation Without State Pattern

![Bad Design: Conditional State Machine](UML/Bad_Conditional_State_Machine.puml)

```cpp
// WARNING: This is the ANTI-PATTERN - showing what NOT to do
class GumballMachine {
public:
    static const int SOLD_OUT = 0;
    static const int NO_QUARTER = 1;
    static const int HAS_QUARTER = 2;
    static const int SOLD = 3;

    int state = SOLD_OUT;
    int count = 0;

    GumballMachine(int count) : count(count) {
        if (count > 0) {
            state = NO_QUARTER;
        }
    }

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

    void ejectQuarter() {
        if (state == HAS_QUARTER) {
            std::cout << "Quarter returned\n";
            state = NO_QUARTER;
        } else if (state == NO_QUARTER) {
            std::cout << "You haven't inserted a quarter\n";
        } else if (state == SOLD) {
            std::cout << "Sorry, you already turned the crank\n";
        } else if (state == SOLD_OUT) {
            std::cout << "You can't eject, you haven't inserted a quarter yet\n";
        }
    }

    void turnCrank() {
        if (state == SOLD) {
            std::cout << "Turning twice doesn't get you another gumball!\n";
        } else if (state == NO_QUARTER) {
            std::cout << "You turned but there's no quarter\n";
        } else if (state == SOLD_OUT) {
            std::cout << "You turned, but there are no gumballs\n";
        } else if (state == HAS_QUARTER) {
            std::cout << "You turned...\n";
            state = SOLD;
            dispense();
        }
    }

    void dispense() {
        if (state == SOLD) {
            std::cout << "A gumball comes rolling out the slot\n";
            count--;
            if (count == 0) {
                std::cout << "Oops, out of gumballs!\n";
                state = SOLD_OUT;
            } else {
                state = NO_QUARTER;
            }
        } else if (state == NO_QUARTER) {
            std::cout << "You need to pay first\n";
        } else if (state == SOLD_OUT) {
            std::cout << "No gumball dispensed\n";
        } else if (state == HAS_QUARTER) {
            std::cout << "No gumball dispensed\n";
        }
    }
};
```

### What's Wrong With This Approach?

#### 1. Violation of Open/Closed Principle

**Pain Point**: Want to add a "WINNER" state (1 in 10 chance of winning 2 gumballs)?

```cpp
// Now EVERY method needs modification!
void insertQuarter() {
    if (state == HAS_QUARTER) {
        // ...
    } else if (state == NO_QUARTER) {
        // ...
    } else if (state == SOLD_OUT) {
        // ...
    } else if (state == SOLD) {
        // ...
    } else if (state == WINNER) {  // NEW - must add to EVERY method!
        std::cout << "Please wait, we're already giving you a gumball\n";
    }
}

void ejectQuarter() {
    // Another conditional chain that needs WINNER added...
}

void turnCrank() {
    // Another conditional chain that needs WINNER added...
    // Plus, now we need logic to decide between SOLD and WINNER!
}

void dispense() {
    // Another conditional chain that needs WINNER added...
    // Plus, WINNER needs to dispense TWO gumballs!
}
```

**The Nightmare**: Adding ONE new state requires modifying EVERY action method. This violates the Open/Closed Principle (open for extension, closed for modification).

#### 2. Code Duplication and Maintenance Hell

Each action method repeats the same state checks:

```cpp
// This pattern repeats in EVERY method:
if (state == HAS_QUARTER) {
    // behavior for HAS_QUARTER state
} else if (state == NO_QUARTER) {
    // behavior for NO_QUARTER state
} else if (state == SOLD_OUT) {
    // behavior for SOLD_OUT state
} else if (state == SOLD) {
    // behavior for SOLD state
}
```

**Maintenance Problem**: If a state's behavior needs to change, you must hunt through ALL methods to find where that state is handled. State-specific logic is scattered across the entire class.

#### 3. Difficult to Understand State Transitions

State transitions are buried inside conditional blocks:

```cpp
void turnCrank() {
    // ...
    else if (state == HAS_QUARTER) {
        std::cout << "You turned...\n";
        state = SOLD;  // Hidden transition!
        dispense();
    }
}

void dispense() {
    if (state == SOLD) {
        // ...
        if (count == 0) {
            state = SOLD_OUT;  // Another hidden transition!
        } else {
            state = NO_QUARTER;  // Yet another hidden transition!
        }
    }
}
```

**Understanding Problem**: To understand all transitions FROM a particular state, you must read every method and find all places where that state is checked. There's no clear documentation of the state machine's structure.

#### 4. Testing Nightmare

Each method has multiple code paths (one for each state). Testing requires:

```cpp
// To test insertQuarter(), you need 4 test cases:
test_insertQuarter_when_NO_QUARTER();
test_insertQuarter_when_HAS_QUARTER();
test_insertQuarter_when_SOLD_OUT();
test_insertQuarter_when_SOLD();

// Multiply this by the number of actions (4) and states (4+):
// That's 16+ test cases just for basic functionality!
// And it grows quadratically with new states!
```

#### 5. No Encapsulation of State-Specific Behavior

All state logic lives in the context class, creating a God Object:

```cpp
class GumballMachine {
    // This class knows EVERYTHING about EVERY state
    // It has multiple reasons to change (one for each state)
    // Violates Single Responsibility Principle!
};
```

### Summary: Why This Approach Fails

| Problem | Impact |
|---------|--------|
| **Not Extensible** | Adding states requires modifying every method |
| **Code Duplication** | Same state checks repeated everywhere |
| **Hidden Transitions** | State flow is difficult to understand |
| **Testing Complexity** | Combinatorial explosion of test cases |
| **Poor Encapsulation** | All state logic in one giant class |
| **Maintenance Hell** | Changes to one state affect entire class |

**The Root Cause**: State-dependent behavior is implemented as **conditional logic** rather than **polymorphic delegation**.

---

## Design Principles

The State Pattern exemplifies several key design principles:

### 1. Open/Closed Principle

**Principle**: Classes should be open for extension but closed for modification.

**How State Pattern Achieves This**:

```cpp
// Adding a new state (e.g., WINNER state in gumball machine)
// requires NO modification to existing code

// Just add a new state class:
class WinnerState : public State {
    void dispense(GumballMachine* machine) override {
        std::cout << "YOU'RE A WINNER! You get two gumballs!\n";
        machine->releaseBall();
        if (machine->getCount() > 0) {
            machine->releaseBall();
            machine->setState(machine->getNoQuarterState());
        } else {
            machine->setState(machine->getSoldOutState());
        }
    }
};

// And modify HasQuarterState to transition to it:
class HasQuarterState : public State {
    void turnCrank(GumballMachine* machine) override {
        // Add winner logic
        if (random() % 10 == 0 && machine->getCount() > 1) {
            machine->setState(machine->getWinnerState());
        } else {
            machine->setState(machine->getSoldState());
        }
    }
};

// NO OTHER CLASSES NEED TO CHANGE!
```

**Contrast with Conditional Approach**: Every method in GumballMachine would need modification to handle the WINNER state.

### 2. Single Responsibility Principle

**Principle**: A class should have only one reason to change.

**How State Pattern Achieves This**:

```cpp
// Each state class has ONE responsibility:
// Define behavior for that specific state

class NoQuarterState : public State {
    // This class changes ONLY if NO_QUARTER state behavior changes
    void insertQuarter(GumballMachine* machine) override;
    void ejectQuarter(GumballMachine* machine) override;
    void turnCrank(GumballMachine* machine) override;
    void dispense(GumballMachine* machine) override;
};

// Context has ONE responsibility:
// Maintain current state and delegate to it
class GumballMachine {
    std::unique_ptr<State> state;  // Current state
public:
    void insertQuarter() { state->insertQuarter(this); }
    void setState(std::unique_ptr<State> s) { state = std::move(s); }
};
```

**Contrast with Conditional Approach**: GumballMachine class had responsibilities for ALL states (4-11 reasons to change).

### 3. Encapsulate What Varies

**Principle**: Identify aspects that vary and separate them from what stays the same.

**What Varies**: Behavior in each state
**What Stays the Same**: The actions (insertQuarter, ejectQuarter, etc.)

**How State Pattern Achieves This**:

```cpp
// The interface (what stays the same)
class State {
public:
    virtual void insertQuarter(GumballMachine* machine) = 0;
    virtual void ejectQuarter(GumballMachine* machine) = 0;
    virtual void turnCrank(GumballMachine* machine) = 0;
    virtual void dispense(GumballMachine* machine) = 0;
};

// The varying implementations (encapsulated in separate classes)
class NoQuarterState : public State { /* behavior for NO_QUARTER */ };
class HasQuarterState : public State { /* behavior for HAS_QUARTER */ };
class SoldState : public State { /* behavior for SOLD */ };
```

### 4. Favor Composition Over Inheritance

**Principle**: Use HAS-A relationships over IS-A relationships for flexibility.

**How State Pattern Achieves This**:

```cpp
class GumballMachine {
    // HAS-A state (composition)
    std::unique_ptr<State> state;

    // Can change state at runtime
    void setState(std::unique_ptr<State> newState) {
        state = std::move(newState);
    }
};

// NOT using inheritance:
// class GumballMachineNoQuarter : public GumballMachine { };
// class GumballMachineHasQuarter : public GumballMachine { };
// ^ This would be inflexible - can't change "class" at runtime!
```

**Benefit**: The machine can change its behavior dynamically by changing its state object.

### 5. Dependency Inversion Principle

**Principle**: Depend on abstractions, not concrete classes.

**How State Pattern Achieves This**:

```cpp
class GumballMachine {
    // Depends on abstraction (State interface)
    std::unique_ptr<State> state;

    // Not on concrete states:
    // NoQuarterState* state;  // WRONG - tight coupling
};

// Client code depends on State interface:
void transition(GumballMachine* machine, std::unique_ptr<State> newState) {
    machine->setState(std::move(newState));
}
```

---

## The Solution: State Pattern

### The Key Insight

Instead of asking "what is the current state?" and then choosing behavior, we ask "what is the current state object?" and then delegate to it.

**Procedural Approach**:
```
if (state == NO_QUARTER) {
    // do NO_QUARTER behavior
} else if (state == HAS_QUARTER) {
    // do HAS_QUARTER behavior
}
```

**State Pattern Approach**:
```
state->insertQuarter(this);  // State object knows what to do!
```

### The Transformation

#### Step 1: Define the State Interface

```cpp
class State {
public:
    virtual ~State() = default;
    virtual void insertQuarter(GumballMachine* machine) = 0;
    virtual void ejectQuarter(GumballMachine* machine) = 0;
    virtual void turnCrank(GumballMachine* machine) = 0;
    virtual void dispense(GumballMachine* machine) = 0;
};
```

**Purpose**: Defines the interface for all state-dependent operations.

#### Step 2: Implement Concrete States

```cpp
class NoQuarterState : public State {
    void insertQuarter(GumballMachine* machine) override {
        std::cout << "You inserted a quarter\n";
        machine->setState(machine->getHasQuarterState());
    }

    void ejectQuarter(GumballMachine* machine) override {
        std::cout << "You haven't inserted a quarter\n";
    }

    void turnCrank(GumballMachine* machine) override {
        std::cout << "You turned, but there's no quarter\n";
    }

    void dispense(GumballMachine* machine) override {
        std::cout << "You need to pay first\n";
    }
};

class HasQuarterState : public State {
    void insertQuarter(GumballMachine* machine) override {
        std::cout << "You can't insert another quarter\n";
    }

    void ejectQuarter(GumballMachine* machine) override {
        std::cout << "Quarter returned\n";
        machine->setState(machine->getNoQuarterState());
    }

    void turnCrank(GumballMachine* machine) override {
        std::cout << "You turned...\n";
        machine->setState(machine->getSoldState());
    }

    void dispense(GumballMachine* machine) override {
        std::cout << "No gumball dispensed\n";
    }
};

class SoldState : public State {
    void insertQuarter(GumballMachine* machine) override {
        std::cout << "Please wait, we're already giving you a gumball\n";
    }

    void ejectQuarter(GumballMachine* machine) override {
        std::cout << "Sorry, you already turned the crank\n";
    }

    void turnCrank(GumballMachine* machine) override {
        std::cout << "Turning twice doesn't get you another gumball!\n";
    }

    void dispense(GumballMachine* machine) override {
        machine->releaseBall();
        if (machine->getCount() > 0) {
            machine->setState(machine->getNoQuarterState());
        } else {
            std::cout << "Oops, out of gumballs!\n";
            machine->setState(machine->getSoldOutState());
        }
    }
};

class SoldOutState : public State {
    void insertQuarter(GumballMachine* machine) override {
        std::cout << "You can't insert a quarter, the machine is sold out\n";
    }

    void ejectQuarter(GumballMachine* machine) override {
        std::cout << "You can't eject, you haven't inserted a quarter yet\n";
    }

    void turnCrank(GumballMachine* machine) override {
        std::cout << "You turned, but there are no gumballs\n";
    }

    void dispense(GumballMachine* machine) override {
        std::cout << "No gumball dispensed\n";
    }
};
```

**Key Observation**: Each state class contains ONLY the behavior for that specific state. No conditionals needed!

#### Step 3: Context Delegates to State

```cpp
class GumballMachine {
    std::unique_ptr<State> soldOutState;
    std::unique_ptr<State> noQuarterState;
    std::unique_ptr<State> hasQuarterState;
    std::unique_ptr<State> soldState;

    State* state;  // Current state (non-owning pointer)
    int count;

public:
    GumballMachine(int count) : count(count) {
        // Create all state objects
        soldOutState = std::make_unique<SoldOutState>();
        noQuarterState = std::make_unique<NoQuarterState>();
        hasQuarterState = std::make_unique<HasQuarterState>();
        soldState = std::make_unique<SoldState>();

        // Set initial state
        if (count > 0) {
            state = noQuarterState.get();
        } else {
            state = soldOutState.get();
        }
    }

    // Actions simply delegate to current state
    void insertQuarter() {
        state->insertQuarter(this);
    }

    void ejectQuarter() {
        state->ejectQuarter(this);
    }

    void turnCrank() {
        state->turnCrank(this);
        state->dispense(this);  // Automatically dispense after crank
    }

    // Helper methods for states to use
    void setState(State* newState) {
        state = newState;
    }

    void releaseBall() {
        std::cout << "A gumball comes rolling out the slot...\n";
        if (count > 0) {
            count--;
        }
    }

    // Getters for states
    State* getNoQuarterState() { return noQuarterState.get(); }
    State* getHasQuarterState() { return hasQuarterState.get(); }
    State* getSoldState() { return soldState.get(); }
    State* getSoldOutState() { return soldOutState.get(); }
    int getCount() const { return count; }
};
```

### The Beautiful Result

**Before (insertQuarter with conditionals)**:
```cpp
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
```

**After (with State Pattern)**:
```cpp
void insertQuarter() {
    state->insertQuarter(this);  // Just delegate!
}
```

**The Magic**: The context doesn't need to know about states anymore. It just delegates, and the state object knows what to do.

---

## State Pattern Structure

### UML Class Diagram

```
┌─────────────────────┐
│   GumballMachine    │ (Context)
├─────────────────────┤
│ - state: State*     │
│ - count: int        │
├─────────────────────┤
│ + insertQuarter()   │────────┐
│ + ejectQuarter()    │        │ delegates to
│ + turnCrank()       │        │
│ + setState(State*)  │        │
│ + releaseBall()     │        ▼
└─────────────────────┘   ┌──────────────┐
                           │   <<State>>  │ (Interface)
                           ├──────────────┤
                           │ + insertQuarter(machine)
                           │ + ejectQuarter(machine)
                           │ + turnCrank(machine)
                           │ + dispense(machine)
                           └──────────────┘
                                  △
                    ┌─────────────┼─────────────┬───────────┐
                    │             │             │           │
        ┌───────────────┐ ┌──────────────┐ ┌──────────┐ ┌─────────────┐
        │ NoQuarterState│ │HasQuarterState│ │SoldState│ │SoldOutState │
        └───────────────┘ └──────────────┘ └──────────┘ └─────────────┘
```

### Participants

1. **State (Interface)**: Defines interface for encapsulating behavior associated with a particular state
2. **ConcreteState** (NoQuarterState, HasQuarterState, etc.): Implements behavior associated with a state
3. **Context** (GumballMachine): Maintains current state and delegates state-dependent operations to current state object

### Collaborations

1. **Context delegates** state-specific requests to the current ConcreteState object
2. **ConcreteState implements** the behavior appropriate for its state
3. **ConcreteState can change** the context's state by calling `context->setState(newState)`

---

## State Transitions and Responsibilities

### State Transition Diagram

```
                    ┌──────────────┐
                    │  SOLD_OUT    │◄────────────────┐
                    └──────┬───────┘                 │
                           │ refill()                │
                           ▼                         │
                    ┌──────────────┐        count == 0
                    │ NO_QUARTER   │◄───────────┐    │
                    └──────┬───────┘            │    │
                           │ insertQuarter()    │    │
                           ▼                    │    │
                    ┌──────────────┐            │    │
              ┌────►│ HAS_QUARTER  │            │    │
              │     └──────┬───────┘            │    │
              │            │ turnCrank()        │    │
              │            ▼                    │    │
              │     ┌──────────────┐            │    │
              │     │    SOLD      │────────────┘    │
              │     └──────────────┘ dispense()      │
              │            │    (count > 0)          │
              │            └─────────────────────────┘
              │                     dispense()
              │ ejectQuarter()      (count == 0)
              └────────────────────────────
```

### Who Handles State Transitions?

**Design Question**: Should the Context or the ConcreteStates decide state transitions?

**Answer**: In this pattern, **ConcreteStates** handle transitions.

**Rationale**:

```cpp
// State objects know their transitions
class HasQuarterState : public State {
    void turnCrank(GumballMachine* machine) override {
        std::cout << "You turned...\n";
        // This state knows where to go next
        machine->setState(machine->getSoldState());
    }
};

// Alternative (not recommended here):
class GumballMachine {
    void turnCrank() {
        state->turnCrank(this);
        // Context decides transition
        if (/* some condition */) {
            setState(soldState.get());
        }
    }
};
```

**Trade-off**:

- **States handle transitions** (used here):
  - Pro: States are self-contained and independent
  - Pro: Easy to add new states
  - Con: States must know about other states (coupling)

- **Context handles transitions**:
  - Pro: Centralized transition logic
  - Pro: States don't need to know about each other
  - Con: Context must know about all state transitions
  - Con: Adding states requires modifying context

**For the gumball machine**: States handle transitions because each state's behavior is tightly coupled with where it goes next.

### Responsibility Distribution

| Class | Responsibilities |
|-------|-----------------|
| **GumballMachine** | - Maintain current state<br>- Delegate actions to state<br>- Provide helper methods (releaseBall, getCount)<br>- Provide access to state objects |
| **State** | - Define interface for state-dependent operations |
| **NoQuarterState** | - Handle actions when no quarter is inserted<br>- Transition to HasQuarter when quarter inserted |
| **HasQuarterState** | - Handle actions when quarter is present<br>- Transition to Sold when crank turned<br>- Transition to NoQuarter when quarter ejected |
| **SoldState** | - Dispense gumball<br>- Transition to NoQuarter or SoldOut based on count |
| **SoldOutState** | - Handle actions when machine is empty<br>- Reject all operations except refill |

---

## Benefits and Trade-offs

### Benefits

#### 1. Eliminates Conditional Logic

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
    state->insertQuarter(this);  // Clean!
}
```

**Impact**: Code is cleaner, easier to read, and easier to maintain.

#### 2. Localizes State-Specific Behavior

**Before**: State behavior scattered across multiple methods in GumballMachine
**After**: All NO_QUARTER behavior in NoQuarterState class

```cpp
// Everything about NO_QUARTER state is in one place
class NoQuarterState : public State {
    // All insertQuarter behavior for this state
    void insertQuarter(GumballMachine* machine) override { /* ... */ }
    // All ejectQuarter behavior for this state
    void ejectQuarter(GumballMachine* machine) override { /* ... */ }
    // All turnCrank behavior for this state
    void turnCrank(GumballMachine* machine) override { /* ... */ }
    // All dispense behavior for this state
    void dispense(GumballMachine* machine) override { /* ... */ }
};
```

**Impact**: Easy to understand and modify a state's behavior. Changes are localized.

#### 3. Makes State Transitions Explicit

**Before**: Hidden in conditional blocks
```cpp
if (state == HAS_QUARTER) {
    state = SOLD;  // Hidden transition
}
```

**After**: Explicit method calls
```cpp
machine->setState(machine->getSoldState());  // Clear transition
```

**Impact**: State machine structure is visible and documentable.

#### 4. Extensibility (Open/Closed Principle)

**Adding WinnerState**:

```cpp
// Just add new state class - no modification to existing code!
class WinnerState : public State {
    void dispense(GumballMachine* machine) override {
        std::cout << "YOU'RE A WINNER! You get two gumballs!\n";
        machine->releaseBall();
        if (machine->getCount() > 0) {
            machine->releaseBall();
            if (machine->getCount() > 0) {
                machine->setState(machine->getNoQuarterState());
            } else {
                machine->setState(machine->getSoldOutState());
            }
        }
    }
};
```

**Impact**: New states can be added with minimal changes to existing code.

#### 5. Better Testing

```cpp
// Test a single state in isolation
TEST(NoQuarterState, InsertQuarterTransitionsToHasQuarter) {
    GumballMachine machine(5);
    NoQuarterState state;

    state.insertQuarter(&machine);

    EXPECT_EQ(machine.getCurrentState(), machine.getHasQuarterState());
}
```

**Impact**: Each state can be unit tested independently. No need to set up complex scenarios.

### Trade-offs

#### 1. Increased Number of Classes

**Cost**: Instead of 1 class (GumballMachine), you have 5+ classes (GumballMachine + 4 states)

```cpp
// Without pattern: 1 class
class GumballMachine { /* everything */ };

// With pattern: 5 classes
class State { /* interface */ };
class NoQuarterState : public State { /* ... */ };
class HasQuarterState : public State { /* ... */ };
class SoldState : public State { /* ... */ };
class SoldOutState : public State { /* ... */ };
class GumballMachine { /* context */ };
```

**Is it worth it?**: Yes, because each class is simpler, more focused, and easier to understand than the monolithic alternative.

#### 2. State Objects Need Context Reference

**Issue**: States need to call back to the context

```cpp
class HasQuarterState : public State {
    void turnCrank(GumballMachine* machine) override {
        // Need to access context's methods
        machine->setState(machine->getSoldState());
    }
};
```

**Potential Problem**: Circular dependency (State knows about Context, Context knows about State)

**Solution**: Forward declaration and passing context as parameter (not storing it)

#### 3. State Transition Coupling

**Issue**: States need to know about other states

```cpp
class SoldState : public State {
    void dispense(GumballMachine* machine) override {
        machine->releaseBall();
        if (machine->getCount() > 0) {
            // Must know about NoQuarterState
            machine->setState(machine->getNoQuarterState());
        } else {
            // Must know about SoldOutState
            machine->setState(machine->getSoldOutState());
        }
    }
};
```

**Mitigation**: Context provides getters for state objects, centralizing state object creation and access.

#### 4. Memory Overhead

**Cost**: Each state object takes memory

```cpp
class GumballMachine {
    std::unique_ptr<State> soldOutState;     // Allocation
    std::unique_ptr<State> noQuarterState;   // Allocation
    std::unique_ptr<State> hasQuarterState;  // Allocation
    std::unique_ptr<State> soldState;        // Allocation
};
```

**When is this a problem?**: If you have millions of state machines (e.g., one per TCP connection)

**Solutions**:
- **Flyweight Pattern**: Share state objects across contexts (if states are stateless)
- **State Pooling**: Reuse state objects
- **Lazy Creation**: Create states only when needed

### When to Use State Pattern

**Use When**:

1. An object's behavior depends on its state
2. Operations have large, multipart conditional statements based on state
3. State transitions are complex
4. You need to add new states frequently

**Don't Use When**:

1. You have very few states (2-3) with simple behavior
2. State transitions are trivial
3. States don't have different behaviors for the same action
4. Memory is extremely constrained (embedded systems with thousands of state machines)

---

## State vs Strategy Pattern

### The Confusion

State and Strategy patterns have nearly **identical structure** but **different intent**. Understanding the difference is crucial.

### Structural Similarity

Both patterns have:

```cpp
// Both have a context
class Context {
    SomeInterface* strategy/state;
};

// Both have an interface
class SomeInterface {
    virtual void algorithm/operation() = 0;
};

// Both have concrete implementations
class ConcreteA : public SomeInterface { /* ... */ };
class ConcreteB : public SomeInterface { /* ... */ };
```

### Key Differences

| Aspect | Strategy Pattern | State Pattern |
|--------|-----------------|---------------|
| **Intent** | Define a family of algorithms, make them interchangeable | Allow object to change behavior when state changes |
| **Who Changes** | Client chooses strategy | Context or state changes state |
| **Transitions** | No transitions between strategies | States transition to other states |
| **Awareness** | Strategies are independent | States may know about other states |
| **Purpose** | Vary algorithm | Vary behavior based on state |
| **Replacement** | Alternative to subclassing | Alternative to conditionals |

### Intent Comparison

**Strategy Pattern Intent**:
```cpp
// Client chooses compression algorithm
class FileCompressor {
    std::unique_ptr<CompressionStrategy> strategy;
public:
    // Client explicitly sets strategy
    void setStrategy(std::unique_ptr<CompressionStrategy> s) {
        strategy = std::move(s);
    }

    void compress(const File& file) {
        strategy->compress(file);  // Use chosen algorithm
    }
};

// Client code:
FileCompressor compressor;
compressor.setStrategy(std::make_unique<ZipCompression>());
compressor.compress(file);

// Later, client decides to change algorithm
compressor.setStrategy(std::make_unique<GzipCompression>());
compressor.compress(file);
```

**State Pattern Intent**:
```cpp
// State changes based on internal logic, not client choice
class GumballMachine {
    State* state;
public:
    void insertQuarter() {
        // State handles action AND transitions
        state->insertQuarter(this);
        // Client doesn't choose state - states transition themselves
    }
};

// Client code (notice: client doesn't set state):
GumballMachine machine(10);
machine.insertQuarter();  // State changes internally
machine.turnCrank();      // State changes again
// Client doesn't control state transitions!
```

### Who Controls Changes

**Strategy Pattern**: Client decides which strategy to use
```cpp
// Client code
if (userPreference == "fast") {
    sorter.setStrategy(std::make_unique<QuickSort>());
} else if (userPreference == "stable") {
    sorter.setStrategy(std::make_unique<MergeSort>());
}
```

**State Pattern**: Context or states decide transitions
```cpp
// State code (not client code)
void HasQuarterState::turnCrank(GumballMachine* machine) {
    // State decides to transition
    machine->setState(machine->getSoldState());
}
```

### State Transitions

**Strategy Pattern**: No concept of "transitioning" between strategies
```cpp
class CompressionStrategy {
    virtual void compress(File& file) = 0;
    // Strategies don't transition to other strategies
};
```

**State Pattern**: States explicitly transition to other states
```cpp
class SoldState : public State {
    void dispense(GumballMachine* machine) override {
        machine->releaseBall();
        if (machine->getCount() > 0) {
            // Transition to different state
            machine->setState(machine->getNoQuarterState());
        } else {
            // Or another state
            machine->setState(machine->getSoldOutState());
        }
    }
};
```

### Conceptual Purpose

**Strategy Pattern**: "Here are different ways to accomplish the same goal. Pick one."

Examples:
- Different sorting algorithms (QuickSort, MergeSort, HeapSort)
- Different compression algorithms (ZIP, GZIP, BZIP2)
- Different payment methods (CreditCard, PayPal, Bitcoin)

**State Pattern**: "The object behaves differently in different states, and transitions between those states."

Examples:
- TCP connection lifecycle (CLOSED → LISTEN → ESTABLISHED → ...)
- Document states (Draft → Review → Published)
- Gumball machine (NoQuarter → HasQuarter → Sold)

### Example: Sorting (Strategy) vs Connection (State)

**Strategy Example**: Sorting
```cpp
class Sorter {
    std::unique_ptr<SortStrategy> strategy;
public:
    void setStrategy(std::unique_ptr<SortStrategy> s) {
        strategy = std::move(s);
    }

    void sort(std::vector<int>& data) {
        strategy->sort(data);
    }
};

// Usage:
Sorter sorter;
sorter.setStrategy(std::make_unique<QuickSort>());
sorter.sort(data);

// Client explicitly chooses different strategy
sorter.setStrategy(std::make_unique<MergeSort>());
sorter.sort(data);

// Strategies don't "transition" - client chooses
```

**State Example**: TCP Connection
```cpp
class TcpConnection {
    std::unique_ptr<TcpState> state;
public:
    void open() {
        // State handles action and may transition
        state->open(this);
    }

    void close() {
        state->close(this);
    }
};

// Usage:
TcpConnection conn;
conn.open();   // CLOSED → SYN_SENT (internal transition)
// ... receives SYN-ACK → ESTABLISHED (internal transition)
conn.close();  // ESTABLISHED → FIN_WAIT_1 (internal transition)

// Client doesn't choose states - they transition automatically
```

### Practical Guideline

**Ask yourself**:

1. **Does the client choose the behavior?**
   - Yes → Likely Strategy Pattern
   - No → Likely State Pattern

2. **Do the "states/strategies" transition between each other?**
   - Yes → State Pattern
   - No → Strategy Pattern

3. **Is there a state machine diagram?**
   - Yes → State Pattern
   - No → Strategy Pattern

4. **Does behavior depend on internal state or client preference?**
   - Internal state → State Pattern
   - Client preference → Strategy Pattern

---

## Implementation Guidelines

### 1. Start with the State Machine Diagram

Before coding, draw the state diagram:

```
States: [List all states]
Transitions: [For each state, list what transitions to what]
Actions: [What actions trigger transitions]
```

### 2. Implement State Interface First

```cpp
class State {
public:
    virtual ~State() = default;
    // One method per action
    virtual void action1(Context* ctx) = 0;
    virtual void action2(Context* ctx) = 0;
    // ...
};
```

### 3. Implement States One at a Time

For each state:

1. Create state class
2. Implement each action method
3. Determine transitions (which state comes next)
4. Write unit tests

### 4. Decide on State Ownership Strategy

Choose based on:

- Number of states: Few → Context owns all; Many → Transfer ownership
- State data: Stateless → Share states; Stateful → Unique states
- Performance: Critical → Context owns all; Not critical → Transfer ownership

### 5. Consider State Entry/Exit Actions

If initialization/cleanup is needed:

```cpp
class State {
    virtual void onEnter(Context* ctx) {}
    virtual void onExit(Context* ctx) {}
};
```

### 6. Document State Transitions

```cpp
class SoldState : public State {
    /**
     * Dispenses gumball and transitions to:
     * - NoQuarterState if count > 0
     * - SoldOutState if count == 0
     */
    void dispense(GumballMachine* machine) override;
};
```

### 7. Test Each State Independently

```cpp
TEST(SoldState, DispenseTransitionsToNoQuarter) {
    GumballMachine machine(5);
    SoldState state;
    machine.setState(&state);

    state.dispense(&machine);

    EXPECT_EQ(machine.getCurrentState(), machine.getNoQuarterState());
}
```

---

## Pattern Relationships

### State and Other Patterns

#### 1. State + Strategy

**Combination**: States can use Strategy internally

```cpp
class HasQuarterState : public State {
    std::unique_ptr<WinningStrategy> winningStrategy;

    void turnCrank(GumballMachine* machine) override {
        if (winningStrategy->isWinner()) {
            machine->setState(machine->getWinnerState());
        } else {
            machine->setState(machine->getSoldState());
        }
    }
};
```

**Use Case**: Separating state behavior from algorithms used within that state

#### 2. State + Singleton

**Combination**: Share state objects as Singletons

```cpp
class NoQuarterState : public State {
    static NoQuarterState instance;
public:
    static NoQuarterState& getInstance() {
        return instance;
    }
private:
    NoQuarterState() = default;  // Private constructor
};
```

**Use Case**: Memory optimization when states are stateless

#### 3. State + Flyweight

**Combination**: Pool state objects for reuse

```cpp
class StatePool {
    std::array<std::unique_ptr<State>, NUM_STATES> states;
public:
    State* getState(StateType type) {
        if (!states[type]) {
            states[type] = createState(type);
        }
        return states[type].get();
    }
};
```

**Use Case**: Many context objects, few state types, memory constrained

#### 4. State + Command

**Combination**: Commands can trigger state transitions

```cpp
class InsertQuarterCommand : public Command {
    GumballMachine* machine;
public:
    void execute() override {
        machine->insertQuarter();  // Triggers state transition
    }

    void undo() override {
        // Restore previous state
        machine->setState(previousState);
    }
};
```

**Use Case**: Undoable state transitions, transaction-like behavior

#### 5. State + Observer

**Combination**: Notify observers when state changes

```cpp
class GumballMachine {
    std::vector<Observer*> observers;

    void setState(State* newState) {
        State* oldState = state;
        state = newState;
        notifyStateChange(oldState, newState);
    }
};
```

**Use Case**: UI updates, logging, monitoring

---

## Summary

### Key Takeaways

1. **State Pattern** encapsulates state-specific behavior into separate state objects, eliminating conditional logic

2. **Problem Solved**: Giant if-else or switch statements that handle state-dependent behavior

3. **Benefits**:
   - Eliminates conditionals
   - Localizes state-specific behavior
   - Makes state transitions explicit
   - Easy to add new states (Open/Closed Principle)
   - Better testing (isolated state testing)

4. **Trade-offs**:
   - More classes
   - State objects need context reference
   - States may need to know about other states

5. **State vs Strategy**:
   - State: Behavior depends on internal state, transitions happen automatically
   - Strategy: Client chooses algorithm, no transitions

6. **C++ Considerations**:
   - Choose ownership strategy (context owns all vs transfer ownership)
   - Use forward declarations to avoid circular dependencies
   - Virtual dispatch is efficient
   - Prefer stateless states when possible

7. **Real-World**: TCP state machines, document workflows, game AI, media players, transactions

### When to Use State Pattern

**Use State Pattern When**:
- Object behavior depends on its state
- Operations have large conditional statements based on state
- State transitions are complex or numerous
- You need to add new states frequently
- State logic is scattered across multiple methods

**Don't Use When**:
- Very few states (2-3) with simple behavior
- State transitions are trivial
- States don't have different behaviors
- Memory is severely constrained

### Design Principles Demonstrated

- **Open/Closed Principle**: Open for extension (new states), closed for modification
- **Single Responsibility**: Each state class has one reason to change
- **Encapsulate What Varies**: State-specific behavior is encapsulated
- **Favor Composition**: Context HAS-A state, not IS-A state
- **Dependency Inversion**: Depend on State abstraction, not concrete states

---

## Further Reading

- **Gang of Four**: "Design Patterns: Elements of Reusable Object-Oriented Software" - State Pattern (page 305)
- **Head First Design Patterns**: Chapter 10 - State Pattern
- **RFC 793**: Transmission Control Protocol - Section 3.2 (State Machine)
- **Martin Fowler**: "Refactoring" - Replace Conditional with Polymorphism
- **Robert C. Martin**: "Clean Code" - Chapter 6 (Objects and Data Structures)

---

**Pattern Family**: Behavioral Patterns
**Related Patterns**: Strategy, Command, Observer, Singleton, Flyweight
**Architectural Level**: Object Behavioral Pattern
**Complexity**: Medium
**Frequency of Use**: High (especially in embedded systems, network stacks, UI frameworks)
