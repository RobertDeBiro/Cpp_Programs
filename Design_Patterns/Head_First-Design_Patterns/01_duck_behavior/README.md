# Strategy Pattern - Duck Behavior

## Overview

Demonstration of the **Strategy Pattern** using a duck simulation. Shows how to encapsulate varying behaviors (flying and quacking) into separate strategy objects, allowing runtime behavior changes.

## Key Concepts

- **Composition over Inheritance:** Ducks HAS-A behavior instead of IS-A behavior type
- **Encapsulate what varies:** Fly and quack behaviors extracted into separate hierarchies
- **Program to interfaces:** Duck depends on behavior interfaces, not concrete implementations
- **Runtime flexibility:** Change duck behaviors dynamically using setter methods

## Project Structure

```
01_duck_behavior/
├── CMakeLists.txt          # Build configuration
├── main.cpp                # Main program entry point
├── inc/                    # Header files
│   ├── Duck.h
│   ├── FlyBehavior.h
│   ├── QuackBehavior.h
│   ├── FlyWithWings.h
│   ├── FlyNoWay.h
│   ├── FlyRocketPowered.h
│   ├── Quack.h
│   ├── MuteQuack.h
│   ├── Squeak.h
│   ├── MallardDuck.h
│   └── ModelDuck.h
├── src/                    # Source files (empty for header-only implementation)
├── out/
│   └── build/              # Build output directory
├── scripts/                # Build and run scripts
│   ├── conf.sh            # Configure CMake
│   ├── build.sh           # Build project
│   ├── run.sh             # Run executable
│   └── all.sh             # Run all steps (configure + build + run)
├── UML/                    # UML diagrams
│   └── diagram.puml
├── Strategy_Pattern.md     # Comprehensive pattern analysis
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
./mini_duck_simulator
```

## Expected Output

```
=== Mallard Duck ===
Quack
I'm flying!!

=== Model Duck ===
I can't fly

--- Attaching rocket to model duck ---
I'm flying with a rocket!
```

## Files

### Behavior Interfaces (in `inc/`)

- `FlyBehavior.h` - Interface for flying strategies
- `QuackBehavior.h` - Interface for quacking strategies

### Fly Strategies (in `inc/`)

- `FlyWithWings.h` - Standard wing-based flight
- `FlyNoWay.h` - No flying ability
- `FlyRocketPowered.h` - Rocket-powered flight

### Quack Strategies (in `inc/`)

- `Quack.h` - Standard quack
- `MuteQuack.h` - Silent (decoy ducks)
- `Squeak.h` - Squeaking (rubber ducks)

### Context (in `inc/`)

- `Duck.h` - Abstract duck class (context)
- `MallardDuck.h` - Concrete duck (flies with wings, quacks)
- `ModelDuck.h` - Concrete duck (initially can't fly, demonstrates runtime behavior change)

### Client

- `main.cpp` - Demonstration program

## Design Highlights

### Modern C++ Features Used

- **Smart pointers** (`std::unique_ptr`) - Automatic memory management
- **Move semantics** - Efficient behavior swapping
- **Const correctness** - Behavior methods marked `const`
- **Virtual destructors** - Proper cleanup in polymorphic hierarchies
- **Default constructors/destructors** - Using `= default` where appropriate

### Why `std::unique_ptr`?

Each duck **exclusively owns** its behaviors. No sharing is needed, so `unique_ptr` is perfect:

- Zero overhead (no reference counting)
- Clear ownership semantics
- Automatic cleanup (RAII)

## Pattern Benefits Demonstrated

1. **Easy to add new behaviors:** Create new strategy classes without modifying `Duck`
2. **Runtime flexibility:** Change behaviors dynamically (see `ModelDuck` example)
3. **Code reuse:** Share strategies across multiple duck types
4. **Testability:** Test strategies independently of `Duck`

## Architecture

```
Duck (Context)
├── HAS-A FlyBehavior (Strategy Interface)
│   ├── FlyWithWings
│   ├── FlyNoWay
│   └── FlyRocketPowered
└── HAS-A QuackBehavior (Strategy Interface)
    ├── Quack
    ├── MuteQuack
    └── Squeak
```

## Further Reading

See [Strategy_Pattern.md](Strategy_Pattern.md) for detailed architectural analysis, including:

- Problem analysis (bad inheritance design)
- Real-world robotics example
- Design principles explained
- Trade-offs and when to use
- C++ specific considerations
