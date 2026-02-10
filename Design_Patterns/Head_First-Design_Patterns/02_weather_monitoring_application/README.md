# Observer Pattern - Weather Monitoring

## Overview

Demonstration of the **Observer Pattern** using a weather monitoring application. Shows how to establish a one-to-many dependency where multiple observers are automatically notified when the subject's state changes, enabling loose coupling between objects.

## Key Concepts

- **One-to-Many Relationship:** One subject (WeatherData) notifies many observers (displays)
- **Loose Coupling:** Subject doesn't know concrete observer types, only that they implement Observer interface
- **Dynamic Subscription:** Observers can register/unregister at runtime
- **Push vs Pull:** Push model used here (subject pushes data to observers)

## Project Structure

```text
02_weather_monitoring_application/
├── CMakeLists.txt          # Build configuration
├── main.cpp                # Main program entry point
├── inc/                    # Header files
│   ├── Subject.h
│   ├── Observer.h
│   ├── DisplayElement.h
│   ├── WeatherData.h
│   └── CurrentConditionsDisplay.h
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
├── Observer_Pattern.md     # Comprehensive pattern analysis
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
./weather_station
```

## Expected Output

```text
=== Weather Monitoring Station ===

--- Measurement Update 1 ---
Current conditions: 80F degrees and 65% humidity

--- Measurement Update 2 ---
Current conditions: 82F degrees and 70% humidity

--- Measurement Update 3 ---
Current conditions: 78F degrees and 90% humidity

=== Demonstration Complete ===
```

## Files

### Pattern Interfaces (in `inc/`)

- `Subject.h` - Interface for observable objects (subjects)
- `Observer.h` - Interface for observers that receive notifications
- `DisplayElement.h` - Interface for display components

### Concrete Subject (in `inc/`)

- `WeatherData.h` - Concrete subject that maintains weather measurements and notifies observers

### Concrete Observers (in `inc/`)

- `CurrentConditionsDisplay.h` - Observer that displays current weather conditions

### Client

- `main.cpp` - Demonstration program showing subject-observer interaction

## Design Highlights

### Modern C++ Features Used

- **RAII for Auto-Unregistration** - Observers unregister in destructor automatically
- **STL Containers** - `std::vector` for managing observer list
- **Algorithms** - `std::find`, `std::remove_if` for observer management
- **Const Correctness** - Display methods marked `const`
- **Virtual Destructors** - Proper cleanup in polymorphic hierarchies
- **Explicit Constructors** - Prevent implicit conversions

### Why Raw Pointers Here?

For simplicity in this example, raw pointers are used. In production code, consider:

- `std::weak_ptr` for observers (avoids ownership issues)
- Automatic unregistration in observer destructor (RAII)
- See Observer_Pattern.md for smart pointer alternatives

## Pattern Benefits Demonstrated

1. **Loose Coupling:** WeatherData doesn't know about concrete display types
2. **Open/Closed Principle:** Add new observers without modifying WeatherData
3. **Dynamic Subscription:** Observers register/unregister at runtime
4. **Reusability:** Subject and observers can be reused independently

## Architecture

```text
Subject (Interface)
├── registerObserver(Observer*)
├── removeObserver(Observer*)
└── notifyObservers()

Observer (Interface)
└── update(data)

WeatherData (Concrete Subject)
├── implements Subject
├── observers: vector<Observer*>
└── notifies all observers when measurements change

CurrentConditionsDisplay (Concrete Observer)
├── implements Observer + DisplayElement
└── receives updates and displays current conditions
```

## Key Observer Pattern Principles

1. **Define a one-to-many dependency** - One subject, many observers
2. **Notify observers automatically** - When subject state changes
3. **Observers can be added/removed dynamically** - Runtime flexibility
4. **Loose coupling** - Subject only knows Observer interface

## Further Reading

See [Observer_Pattern.md](Observer_Pattern.md) for detailed architectural analysis, including:

- Problem analysis (tightly coupled notification system)
- Real-world network monitoring example
- Design principles explained (loose coupling, one-to-many relationship)
- Trade-offs and when to use (update storms, memory management)
- C++ specific considerations (smart pointers, RAII, `std::function` alternative)
