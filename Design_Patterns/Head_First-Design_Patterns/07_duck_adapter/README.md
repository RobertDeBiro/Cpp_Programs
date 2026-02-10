# Adapter Pattern - Duck/Turkey Adapter

## Overview

Demonstration of the **Adapter Pattern** using a duck/turkey example. Shows how to make classes with incompatible interfaces work together without modifying their source code.

## Key Concepts

- **Interface Adaptation:** Convert one interface to another that clients expect
- **Reuse Without Modification:** Use existing classes without changing their code
- **Open/Closed Principle:** Extend functionality via adapters, not modification
- **Composition Over Inheritance:** Object Adapter uses composition (recommended)
- **Decoupling:** Client depends only on target interface, not adaptee

## Project Structure

```text
07_duck_adapter/
├── CMakeLists.txt              # Build configuration
├── main.cpp                    # Main program entry point
├── inc/                        # Header files
│   ├── Duck.h                  # Target interface
│   ├── MallardDuck.h           # Concrete target implementation
│   ├── Turkey.h                # Adaptee interface
│   ├── WildTurkey.h            # Concrete adaptee implementation
│   └── TurkeyAdapter.h         # Adapter (makes Turkey compatible with Duck)
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
├── Adapter_Pattern.md         # Comprehensive pattern analysis
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
./duck_adapter
```

## Expected Output

```text
=== Adapter Pattern - Duck/Turkey Demonstration ===

--- Testing Turkey directly (incompatible interface) ---
The Turkey says...
Gobble gobble
I'm flying a short distance

--- Testing Duck (target interface) ---
The Duck says...
Quack
I'm flying

--- Testing TurkeyAdapter (adapted interface) ---
The TurkeyAdapter says...
Gobble gobble
I'm flying a short distance
I'm flying a short distance
I'm flying a short distance
I'm flying a short distance
I'm flying a short distance

=== Demonstration Complete ===

Key Observations:
1. testDuck() only knows about Duck interface, not Turkey
2. TurkeyAdapter makes Turkey usable where Duck is expected
3. Turkey's gobble() is adapted to Duck's quack()
4. Turkey's short fly() is called 5 times to match Duck's fly()
5. Neither Duck nor Turkey classes were modified
6. Client code (testDuck) remains unchanged
```

## Files

### Interfaces (in `inc/`)

**Target Interface:**

- `Duck.h` - Interface that client expects (quack, fly)

**Adaptee Interface:**

- `Turkey.h` - Incompatible interface (gobble, fly)

### Concrete Implementations (in `inc/`)

**Concrete Target:**

- `MallardDuck.h` - Standard duck implementing Duck interface

**Concrete Adaptee:**

- `WildTurkey.h` - Turkey with incompatible interface

### Adapter (in `inc/`)

- `TurkeyAdapter.h` - Adapts Turkey interface to Duck interface

### Client

- `main.cpp` - Demonstration program showing adaptation

## Design Highlights

### Modern C++ Features Used

- **Virtual Functions** - Polymorphic interfaces
- **Smart Pointers** (`std::unique_ptr`) - Automatic memory management
- **Virtual Destructors** - Proper cleanup in polymorphic hierarchies
- **Pure Virtual Functions** - Enforce interface implementation
- **Explicit Constructors** - Prevent implicit conversions
- **Const Correctness** - Methods marked appropriately
- **nullptr Safety** - Validation in adapter constructor

### Object Adapter (Composition)

This implementation uses the **Object Adapter** approach:

```cpp
class TurkeyAdapter : public Duck {
private:
    Turkey* turkey;  // Composition - HAS-A Turkey

public:
    explicit TurkeyAdapter(Turkey* t) : turkey(t) {}

    // Adapt Duck interface to Turkey interface
    void quack() override {
        turkey->gobble();  // Translate: quack → gobble
    }

    void fly() override {
        // Adapt behavior: 5 short turkey flights = 1 duck flight
        for (int i = 0; i < 5; ++i) {
            turkey->fly();
        }
    }
};
```

**Why Object Adapter?**

- **Flexibility:** Can adapt any Turkey subclass
- **Composition:** Follows "composition over inheritance" principle
- **Runtime:** Can change adaptee at runtime (if using pointer/reference)
- **Recommended:** Preferred in C++ for most scenarios

**Alternative: Class Adapter (Multiple Inheritance):**

```cpp
class TurkeyAdapter : public Duck, private Turkey {
public:
    void quack() override { gobble(); }  // Direct call to inherited method
    void fly() override { Turkey::fly(); }
};
```

- Less flexible (fixed at compile-time)
- Can override adaptee methods
- Multiple inheritance complications

### Adapter Pattern in Action

```cpp
// 1. Client expects Duck interface
void testDuck(Duck* duck) {
    duck->quack();
    duck->fly();
}

// 2. We have Turkey with incompatible interface
Turkey* turkey = new WildTurkey();
testDuck(turkey);  // ❌ Compilation error - incompatible interface

// 3. Wrap Turkey in TurkeyAdapter
Duck* turkeyAdapter = new TurkeyAdapter(turkey);
testDuck(turkeyAdapter);  // ✅ Works! Turkey adapted to Duck interface

// How it works:
testDuck(turkeyAdapter);
//        ↓
//    Calls: turkeyAdapter->quack()
//        ↓
//    TurkeyAdapter::quack() translates to: turkey->gobble()
//        ↓
//    Turkey gobbles (client thinks it quacked)
```

**Critical Insight:** The adapter acts as a translator. The client (testDuck) has no knowledge of Turkey or TurkeyAdapter - it only knows the Duck interface. Neither Duck nor Turkey classes were modified.

## Pattern Benefits Demonstrated

1. **Reuse Existing Code:** Use Turkey without modifying it
2. **Open/Closed Principle:** Add adapters without modifying Duck, Turkey, or client
3. **Interface Translation:** Adapt both method names (gobble→quack) and behavior (5 short flights = 1 long flight)
4. **Decoupling:** Client depends only on Duck interface
5. **Flexibility:** Can create multiple adapters for different adaptee types
6. **Testability:** Can create mock adapters for testing

## Architecture

```text
┌───────────┐
│  Client   │  ← Works only with Duck interface
│ testDuck()│
└─────┬─────┘
      │ uses
      ↓
┌───────────┐
│   Duck    │  ← Target interface (what client expects)
├───────────┤
│ + quack() │
│ + fly()   │
└───────────┘
      △
      │ implements
┌─────┴──────────┐
│ TurkeyAdapter  │  ← Adapter (translates interfaces)
├────────────────┤
│ - turkey*      │ ───┐
│ + quack()      │    │ holds reference (composition)
│ + fly()        │    │
└────────────────┘    │
                      │ adapts
                      ↓
               ┌──────────┐
               │  Turkey  │  ← Adaptee (incompatible interface)
               ├──────────┤
               │+ gobble()│
               │+ fly()   │
               └──────────┘
```

## Key Adapter Pattern Principles

1. **Target Interface:** Interface that client expects (Duck)
2. **Adaptee:** Existing class with incompatible interface (Turkey)
3. **Adapter:** Makes Adaptee compatible with Target (TurkeyAdapter)
4. **Client:** Uses Target interface, unaware of Adapter or Adaptee
5. **Composition:** Adapter HAS-A Adaptee (Object Adapter approach)

## Comparison: Before vs After

| Aspect | Without Adapter (Before) | With Adapter (After) |
|--------|-------------------------|----------------------|
| **Interface Mismatch** | Cannot use Turkey where Duck expected | Turkey usable via TurkeyAdapter |
| **Code Modification** | Must modify Turkey or client code | No modification needed |
| **Type Checking** | Client littered with type checks | Client works with single interface |
| **Extensibility** | Adding new bird types breaks client | Create new adapter, client unchanged |
| **Testing** | Difficult (requires all bird types) | Easy (mock adapters) |
| **Maintenance** | Changes ripple through codebase | Changes isolated to adapters |

## Real-World Applications

### Embedded Systems (See Adapter_Pattern.md)

```cpp
// Target interface expected by monitoring system
class TemperatureSensor {
public:
    virtual float readTemperature() = 0;  // Returns Celsius
};

// Adaptee: Legacy sensor with incompatible interface
class LegacySensorA {
public:
    int readTemp_Celsius();  // Different return type, different name
};

// Adapter: Makes legacy sensor compatible
class SensorAAdapter : public TemperatureSensor {
    LegacySensorA* sensor;
public:
    float readTemperature() override {
        return static_cast<float>(sensor->readTemp_Celsius());
    }
};

// Client code unchanged - works with uniform interface
void recordTemperature(TemperatureSensor* sensor) {
    float temp = sensor->readTemperature();
    database.store(temp);
}

// Can use legacy sensor via adapter
TemperatureSensor* sensor = new SensorAAdapter(new LegacySensorA());
recordTemperature(sensor);  // Works!
```

**Benefits:**

- Integrate sensors from any vendor without modifying core system
- Uniform interface simplifies application logic
- Easy to add new sensor types (just create new adapter)
- Testable with mock adapters (no real hardware needed)

### Third-Party Library Integration

```cpp
// Your application expects this interface
class Logger {
public:
    virtual void log(const std::string& msg) = 0;
};

// Third-party library has different interface
class ThirdPartyLogger {
public:
    void writeLog(const char* message, int priority);
};

// Adapter bridges the gap
class ThirdPartyLoggerAdapter : public Logger {
    ThirdPartyLogger* logger;
public:
    void log(const std::string& msg) override {
        logger->writeLog(msg.c_str(), 1);  // Adapt interface
    }
};
```

### Legacy Code Integration

Adapter Pattern is essential when integrating legacy systems with new code without modifying the legacy code (which may be in production, shared, or poorly documented).

## Pattern Relationships

### Adapter vs Decorator

- **Adapter:** Changes interface (makes incompatible interfaces compatible)
- **Decorator:** Keeps same interface (adds responsibilities/behavior)

### Adapter vs Facade

- **Adapter:** Makes one interface compatible with another (1-to-1)
- **Facade:** Simplifies complex subsystem (many-to-1)

### Adapter vs Bridge

- **Adapter:** Retrospective (adapts existing interfaces after the fact)
- **Bridge:** Prospective (designed upfront to separate abstraction from implementation)

### Adapter vs Proxy

- **Adapter:** Changes interface
- **Proxy:** Keeps same interface (controls access, adds functionality)

## Further Reading

See [Adapter_Pattern.md](Adapter_Pattern.md) for detailed architectural analysis, including:

- Problem analysis (interface incompatibility, cannot modify source)
- Real-world embedded systems example (multi-vendor temperature sensor adapters)
- Design principles explained (Open/Closed, Dependency Inversion, Single Responsibility)
- Object Adapter vs Class Adapter comparison
- Benefits, trade-offs, and when to use Adapter Pattern
- C++ specific considerations (smart pointers, virtual destructors, explicit constructors)
- Pattern relationships (Decorator, Facade, Bridge, Proxy)

## Summary

The Adapter Pattern enables:

- ✅ **Reuse:** Use existing classes without modification
- ✅ **Interface Translation:** Convert incompatible interfaces
- ✅ **Open/Closed:** Extend via adapters, not modification
- ✅ **Decoupling:** Client depends on target interface only
- ✅ **Flexibility:** Adapt multiple classes to same interface
- ✅ **Testability:** Mock adapters for unit tests

**When to use:** You want to use an existing class with an incompatible interface, cannot modify the existing class (third-party, legacy, shared), and need to integrate it with code expecting a different interface.

**Key Insight:** When interfaces don't match, DON'T modify existing code - create an adapter that translates between the interfaces. This preserves existing functionality while enabling integration.
