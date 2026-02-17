# Singleton Pattern - Hardware Manager

## Overview

This project demonstrates the **Singleton Pattern**, a creational design pattern that ensures a class has only one instance and provides a global point of access to it.

## Pattern Intent

**Singleton Pattern** ensures a class has only one instance, and provides a global point of access to it.

## The Problem

Without the Singleton pattern, you face multiple instance issues:

```cpp
// BAD: Multiple instances of hardware manager
class HardwareManager {
public:
    HardwareManager() {
        // Expensive initialization
        initializeHardware();
    }
    void initializeI2C(int bus) { /* ... */ }
};

// Problem: Each module creates its own instance!
void motorController() {
    HardwareManager hw;  // Instance 1
    hw.initializeI2C(0); // Initializes I2C bus 0
}

void sensorModule() {
    HardwareManager hw;  // Instance 2 (CONFLICT!)
    hw.initializeI2C(0); // Re-initializes same bus!
}
```

**Problems:**
- **Multiple instances** accessing same hardware (conflicts)
- **Expensive initialization** repeated unnecessarily
- **State inconsistency** between instances
- **Resource conflicts** (bus contention, GPIO conflicts)
- **No coordination** between different modules

## The Solution

Singleton pattern ensures only one instance exists:

```cpp
// GOOD: Single instance with controlled access
class HardwareManager {
public:
    static HardwareManager& getInstance() {
        static HardwareManager instance;  // Created once
        return instance;
    }

    // Delete copy operations
    HardwareManager(const HardwareManager&) = delete;
    HardwareManager& operator=(const HardwareManager&) = delete;

private:
    HardwareManager() { /* Initialize once */ }
};

// Both modules use SAME instance
void motorController() {
    auto& hw = HardwareManager::getInstance();  // Same instance
}

void sensorModule() {
    auto& hw = HardwareManager::getInstance();  // Same instance
}
```

## Key Components

### 1. Private Constructor
- **Prevents** direct instantiation
- Only callable from within the class
- Performs expensive initialization once

### 2. Static getInstance() Method
- **Returns** reference to singleton instance
- Creates instance on first call (lazy initialization)
- Returns same instance on subsequent calls

### 3. Deleted Copy Operations
- **Delete** copy constructor
- **Delete** assignment operator
- Prevents accidental copying

### 4. Static Instance Variable
- Holds the single instance
- C++11: Meyer's Singleton (thread-safe static local)

## Implementation Variants

### 1. Meyer's Singleton (Used Here)
```cpp
static HardwareManager& getInstance() {
    static HardwareManager instance;  // Thread-safe in C++11+
    return instance;
}
```
✅ **Thread-safe** (C++11 guarantees)
✅ **Lazy initialization**
✅ **Simple and clean**

### 2. Classic Singleton (Eager Initialization)
```cpp
class Singleton {
    static Singleton instance;  // Initialized at program start
public:
    static Singleton& getInstance() { return instance; }
};
```
✅ **Thread-safe**
❌ **Eager initialization** (may waste resources)

### 3. Double-Checked Locking (Legacy)
```cpp
static Singleton* getInstance() {
    if (instance == nullptr) {
        lock_guard<mutex> lock(mutex);
        if (instance == nullptr) {
            instance = new Singleton();
        }
    }
    return instance;
}
```
⚠️ **Complex and error-prone**
⚠️ **Prefer Meyer's Singleton in C++11+**

## Benefits

1. **Controlled Access**
   - Single point of access
   - Cannot create multiple instances
   - Global accessibility

2. **Resource Efficiency**
   - Expensive initialization once
   - Shared state across application
   - Reduced memory footprint

3. **Coordination**
   - All code uses same instance
   - Consistent state
   - No conflicts

4. **Thread Safety**
   - Meyer's Singleton is thread-safe (C++11+)
   - No manual locking needed
   - Automatic initialization

## Trade-offs

1. **Global State**
   - Can make testing harder
   - Hidden dependencies
   - Tight coupling

2. **Hard to Subclass**
   - Private constructor
   - Static methods

3. **Lifetime Management**
   - Destruction order undefined
   - May cause issues at program exit

## When to Use

✅ **Use Singleton when:**
- Exactly one instance needed (hardware manager, logger, config)
- Global point of access required
- Instance must be accessible from many places
- Lazy initialization desired
- Resource is expensive to create

❌ **Don't use when:**
- Multiple instances acceptable
- Need to pass instance as parameter
- Testing with different instances needed
- Inheritance hierarchy required

## Real-World Applications

- **Hardware Resource Managers** (I2C, SPI, GPIO controllers)
- **Logger Systems** (single log file, coordinated output)
- **Configuration Managers** (application settings)
- **Thread Pools** (shared worker threads)
- **Cache Managers** (single cache instance)
- **Device Drivers** (hardware access layer)

## Project Structure

```
01_singleton_pattern/
├── CMakeLists.txt                 # Build configuration
├── main.cpp                       # Demonstration program
├── inc/                           # Header files
│   └── HardwareManager.h         # Singleton hardware manager
├── src/                           # Source files (empty - header-only)
├── out/build/                     # Build output
├── scripts/                       # Build and run scripts
│   ├── conf.sh                   # Configure CMake
│   ├── build.sh                  # Build project
│   ├── run.sh                    # Run executable
│   └── all.sh                    # Run all steps
├── UML/
│   └── Singleton_Pattern.puml    # Class diagram
├── Singleton.md                  # Detailed pattern analysis
└── README.md                     # This file
```

## Building and Running

### Quick Start (All-in-One)

```bash
cd scripts
./all.sh
```

This runs configuration, build, and execution in sequence.

### Step-by-Step

```bash
# 1. Configure CMake
cd scripts
./conf.sh

# 2. Build the project
./build.sh

# 3. Run the executable
./run.sh
```

## Usage Example

The program demonstrates:

```
=== DEMONSTRATION 1: Same Instance ===
- Getting first instance (triggers construction)
- Getting second instance (returns same instance)
- Verifying addresses are identical

=== DEMONSTRATION 2: Thread Safety ===
- Multiple threads accessing singleton concurrently
- Thread-safe initialization
- Shared state across threads

=== DEMONSTRATION 3: Global State ===
- All modifications visible to all clients
- Consistent hardware state
```

## Code Example

```cpp
#include "HardwareManager.h"

int main() {
    // Get singleton instance (first call creates it)
    HardwareManager& hw1 = HardwareManager::getInstance();
    hw1.initializeI2C(0);

    // Get instance again (returns SAME instance)
    HardwareManager& hw2 = HardwareManager::getInstance();
    hw2.initializeSPI(1);

    // Verify: hw1 and hw2 are the SAME object
    assert(&hw1 == &hw2);

    return 0;
}
```

## Design Principles Applied

1. **Single Responsibility Principle**
   - Class manages its own instance
   - Only one instance exists

2. **Information Hiding**
   - Constructor is private
   - Instance creation controlled

3. **Lazy Initialization**
   - Instance created on first use
   - No waste if never used

## C++ Specific Features

- **Meyer's Singleton**: Static local variables (C++11 thread-safe)
- **Deleted functions**: Prevent copying (C++11)
- **Mutex locking**: Thread-safe operations
- **Reference return**: No pointer management
- **Smart pointers**: Not needed (static storage)

## Related Patterns

- **Factory Method**: Can use Singleton for factory instance
- **Abstract Factory**: Often implemented as Singleton
- **Facade**: May be implemented as Singleton

## Further Reading

- Design Patterns: Elements of Reusable Object-Oriented Software (Gang of Four)
- Effective C++ (Scott Meyers) - Item on Singletons
- Singleton.md (detailed analysis with robotics examples)

## Author Notes

This implementation uses **Meyer's Singleton** (C++11 static local variable), which is the recommended approach in modern C++. It provides thread-safe initialization without manual locking, making it simple, safe, and efficient.

The robotics example demonstrates why Singleton is crucial in embedded systems: hardware resources MUST have exactly one manager to prevent conflicts, ensure initialization efficiency, and maintain consistent state across the entire application.
