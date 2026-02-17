# Adapter Pattern - Comprehensive Analysis

## Pattern Overview

**Adapter Pattern** converts the interface of a class into another interface clients expect. Adapter lets classes work together that couldn't otherwise because of incompatible interfaces.

**Key Intent:** Make existing classes work with others without modifying their source code.

**Also Known As:** Wrapper

**Types:**
- **Object Adapter:** Uses composition (holds reference to adaptee)
- **Class Adapter:** Uses multiple inheritance (inherits from both target and adaptee)

---

## The Problem: Interface Incompatibility

### Bad Architecture Example: Direct Interface Mismatch

```cpp
// BAD: Client expects Duck interface
void processWaterfowl(Duck* duck) {
    duck->quack();
    duck->fly();
}

// But we have Turkey with incompatible interface
class Turkey {
public:
    void gobble();  // NOT quack()!
    void fly();     // Same name, but different behavior (short bursts)
};

// PROBLEM: Cannot pass Turkey to processWaterfowl()
Turkey turkey;
processWaterfowl(&turkey);  // ❌ COMPILATION ERROR!

// WORSE SOLUTION: Modify Turkey class to match Duck interface
class Turkey {
public:
    void quack() { gobble(); }  // ❌ Violates Turkey's original design
    void fly() { /* ... */ }
};
// This breaks Open/Closed Principle and may break existing Turkey clients!
```

### Pain Points

1. **Interface Mismatch**
   - Existing class has incompatible interface
   - Cannot modify existing class (third-party library, legacy code)
   - Client expects specific interface

2. **Cannot Modify Source Code**
   - Third-party libraries (vendor SDKs)
   - Legacy code in production
   - Shared code used by multiple systems
   - License restrictions

3. **Breaking Existing Clients**
   - Modifying interface breaks all existing users
   - Risk of introducing bugs
   - Regression testing nightmare

4. **Tight Coupling**
   - Client code directly depends on specific class
   - Cannot substitute alternative implementations
   - Difficult to test (cannot mock)

5. **Copy-Paste Adaptation**
   - Duplicating code to match interface
   - Maintenance nightmare
   - Bug fixes must be applied everywhere

### Example of Cascading Problems

```cpp
// As system grows, interface mismatches multiply:
class DataLogger {
public:
    void log(Duck* duck) {
        duck->quack();
        duck->fly();
    }
};

// Now we have 5 different bird types with different interfaces:
class Goose { void honk(); void glide(); };
class Chicken { void cluck(); void hop(); };
class Pigeon { void coo(); void flutter(); };
class Turkey { void gobble(); void fly(); };
class Parrot { void squawk(); void soar(); };

// BAD SOLUTION 1: Modify DataLogger for every new type
void log(Duck* duck) { duck->quack(); duck->fly(); }
void log(Goose* goose) { goose->honk(); goose->glide(); }
void log(Chicken* chicken) { chicken->cluck(); chicken->hop(); }
// ... 5 overloads! Violates Open/Closed Principle

// BAD SOLUTION 2: Modify all bird classes to implement Duck interface
// This breaks their original APIs and all existing clients!
```

**Result:** System becomes rigid, fragile, and impossible to maintain.

### UML Diagram: Bad Design

See `UML/Bad_Incompatible_Interfaces.puml` for the class diagram showing the incompatible interfaces problem where clients must deal with different types directly (red-highlighted problem class).

---

## Design Principles

### 1. Open/Closed Principle

**Definition:** Classes should be open for extension but closed for modification.

**Before Adapter Pattern:**

```cpp
// Adding new sensor type requires MODIFYING MonitoringSystem
void recordTemperature(void* sensor, SensorType type) {
    if (type == SENSOR_A) { /* ... */ }
    else if (type == SENSOR_B) { /* ... */ }
    else if (type == SENSOR_C) { /* ... */ }
    else if (type == SENSOR_D) { /* MODIFICATION REQUIRED */ }
}
```

**After Adapter Pattern:**

```cpp
// Adding new sensor type only requires EXTENDING (new adapter class)
class SensorDAdapter : public TemperatureSensor {
    SensorD* sensor;
public:
    float readTemperature() override { return sensor->read(); }
};

// MonitoringSystem unchanged!
void recordTemperature(TemperatureSensor* sensor) {
    float temp = sensor->readTemperature();
    database.store(temp);
}
```

### 2. Dependency Inversion Principle

**Definition:** Depend on abstractions, not concrete classes.

**Before Adapter:**

```cpp
// High-level MonitoringSystem depends on low-level sensor drivers
class MonitoringSystem {
    LegacySensorA* sensorA;  // Direct dependency
    ModernSensorB* sensorB;  // Direct dependency
    I2CSensorC* sensorC;     // Direct dependency
};
```

**After Adapter:**

```cpp
// High-level depends on abstraction (TemperatureSensor interface)
class MonitoringSystem {
    std::vector<TemperatureSensor*> sensors;  // Depends on interface
};
```

### 3. Single Responsibility Principle

**Separation of Concerns:**

- **Sensor driver:** Responsible for hardware communication
- **Adapter:** Responsible for interface translation
- **MonitoringSystem:** Responsible for data collection and storage

Each class has ONE reason to change.

### 4. Program to an Interface

**Key Insight:** Client code should depend on abstract interfaces, not concrete implementations.

```cpp
// Good: Depends on abstraction
void processTemperature(TemperatureSensor* sensor) {
    float temp = sensor->readTemperature();
}

// Bad: Depends on concrete class
void processTemperature(LegacySensorA* sensor) {
    int temp = sensor->readTemp_Celsius();
}
```

---

## The Solution: Adapter Pattern

### Structure (Object Adapter)

```text
┌─────────────────┐
│     Client      │
└────────┬────────┘
         │ uses
         ↓
┌─────────────────┐
│   Target        │  ← Interface client expects
│  (Duck)         │
├─────────────────┤
│ + quack()       │
│ + fly()         │
└─────────────────┘
         △
         │ implements
┌────────┴─────────┐
│   Adapter        │  ← Wraps adaptee
│ (TurkeyAdapter)  │
├──────────────────┤
│ - adaptee        │ ───┐
│ + quack()        │    │ holds reference
│ + fly()          │    │
└──────────────────┘    │
                        │
         ┌──────────────┘
         │ adapts
         ↓
┌──────────────────┐
│   Adaptee        │  ← Class with incompatible interface
│  (Turkey)        │
├──────────────────┤
│ + gobble()       │
│ + fly()          │
└──────────────────┘
```

### Key Components

1. **Target (Duck)**
   - Interface that client expects
   - Defines domain-specific methods

2. **Adapter (TurkeyAdapter)**
   - Implements Target interface
   - Holds reference to Adaptee
   - Translates Target calls to Adaptee calls

3. **Adaptee (Turkey)**
   - Existing class with incompatible interface
   - Provides the actual functionality
   - Cannot be modified

4. **Client (testDuck)**
   - Uses Target interface
   - Unaware of Adapter or Adaptee

### How It Works

```cpp
// 1. Client has code expecting Duck interface
void testDuck(Duck* duck) {
    duck->quack();  // Client calls Target method
    duck->fly();
}

// 2. We have Turkey with incompatible interface
Turkey turkey;

// 3. Cannot pass Turkey directly to testDuck()
testDuck(&turkey);  // ❌ Compilation error

// 4. Wrap Turkey in TurkeyAdapter
Duck* turkeyAdapter = new TurkeyAdapter(&turkey);

// 5. Now can pass adapted Turkey to client
testDuck(turkeyAdapter);  // ✅ Works!
//        ↓
//    Calls: turkeyAdapter->quack()
//        ↓
//    TurkeyAdapter::quack() calls: turkey->gobble()
//        ↓
//    Turkey gobbles
```

**Critical Insight:** The Adapter acts as a translator between two incompatible interfaces. Client code remains unchanged, and Adaptee code remains unchanged. Only the Adapter knows about both interfaces.

### Adapter Implementation

```cpp
class TurkeyAdapter : public Duck {
private:
    Turkey* turkey;  // Adaptee

public:
    explicit TurkeyAdapter(Turkey* t) : turkey(t) {}

    // Translate Duck interface to Turkey interface
    void quack() override {
        turkey->gobble();  // Adapt: quack → gobble
    }

    void fly() override {
        // Turkeys fly short distances
        // Adapt behavior: call fly() 5 times
        for (int i = 0; i < 5; ++i) {
            turkey->fly();
        }
    }
};
```

---

## Benefits and Trade-offs

### Benefits

1. **Reuse Existing Code**
   - Use existing classes without modification
   - Preserve original interface for other clients
   - Avoid breaking changes

2. **Open/Closed Principle**
   - Add new adaptees without modifying client code
   - Create new adapters to support new types
   - Client code remains stable

3. **Single Responsibility**
   - Adapter handles ONLY interface translation
   - Separates interface conversion from business logic
   - Clear separation of concerns

4. **Flexibility**
   - Can adapt multiple different classes to same interface
   - Can create adapters at runtime
   - Can have multiple adapters for same adaptee (different Target interfaces)

5. **Testability**
   - Can create mock adapters for testing
   - Test client code without real adaptees
   - Unit test adapters in isolation

### Trade-offs

1. **Additional Indirection**
   - Extra layer of abstraction
   - Small performance overhead (virtual function call)
   - Mitigated by: Modern compilers optimize well, benefits outweigh cost

2. **Increased Class Count**
   - Each adaptation needs an adapter class
   - More files to maintain
   - Mitigated by: Better organization and extensibility

3. **Complexity for Simple Cases**
   - Overkill for trivial adaptations
   - Mitigated by: Use only when benefits justify the cost

4. **Two-Way Adaptation**
   - Object Adapter: Cannot override adaptee behavior
   - Class Adapter: Can override, but requires multiple inheritance (C++ only)
   - Mitigated by: Choose appropriate adapter type

### When to Use Adapter Pattern

- ✅ Want to use existing class with incompatible interface
- ✅ Cannot modify existing class (third-party, legacy, shared)
- ✅ Want to create reusable class that cooperates with unrelated classes
- ✅ Need to use several existing subclasses with common interface
- ✅ Interface adaptation is complex (requires multiple method translations)
- ❌ Simple type conversion (use explicit conversion instead)
- ❌ Can modify existing class to match interface (direct implementation better)

---

## Pattern Relationships

### Adapter vs Decorator

**Similarity:** Both use composition to wrap objects

**Difference:**
- **Adapter:** Changes interface (makes incompatible interface compatible)
- **Decorator:** Keeps same interface (adds responsibilities/behavior)

```cpp
// Adapter: Duck interface → Turkey implementation
class TurkeyAdapter : public Duck { /* ... */ };

// Decorator: Duck interface → Duck interface with added behavior
class ColoredDuck : public Duck {
    Duck* duck;
    void fly() override {
        cout << "Flying with colorful feathers!";
        duck->fly();
    }
};
```

### Adapter vs Facade

**Similarity:** Both provide simplified interface

**Difference:**
- **Adapter:** Makes one interface compatible with another (1-to-1 mapping)
- **Facade:** Simplifies complex subsystem (many-to-1 mapping)

```cpp
// Adapter: Translate Duck interface to Turkey
class TurkeyAdapter : public Duck { /* adapts Turkey */ };

// Facade: Simplify complex bird management system
class BirdFacade {
    FeedingSystem* feeder;
    TrackingSystem* tracker;
    HealthMonitor* health;
public:
    void dailyCare() {  // Simplifies multiple subsystems
        feeder->distributeFeed();
        tracker->logLocations();
        health->checkVitals();
    }
};
```

### Adapter vs Bridge

**Similarity:** Both separate interface from implementation

**Difference:**
- **Adapter:** Retrospective (adapts existing interfaces)
- **Bridge:** Prospective (designed upfront to separate abstraction from implementation)

### Adapter vs Proxy

**Similarity:** Both wrap objects and forward calls

**Difference:**
- **Adapter:** Changes interface
- **Proxy:** Keeps same interface (controls access, adds lazy loading, etc.)

### Common Combination: Adapter + Factory

```cpp
class SensorFactory {
public:
    static TemperatureSensor* createSensor(SensorType type) {
        switch (type) {
            case SENSOR_A: return new SensorAAdapter(new LegacySensorA());
            case SENSOR_B: return new SensorBAdapter(new ModernSensorB());
            case SENSOR_C: return new SensorCAdapter(new I2CSensorC());
        }
    }
};

// Client uses uniform interface, factory handles adaptation
TemperatureSensor* sensor = SensorFactory::createSensor(SENSOR_A);
float temp = sensor->readTemperature();  // Uniform interface
```

---

## Summary: The Power of Adapter Pattern

**Before Adapter Pattern:**

- Interface incompatibility blocks reuse
- Must modify existing classes (breaks Open/Closed)
- Client code littered with type checks and conversions
- Cannot substitute different implementations
- Difficult to test

**After Adapter Pattern:**

- ✅ **Reuse Existing Code:** Use classes without modification
- ✅ **Open/Closed:** Add new adaptees without changing client
- ✅ **Single Responsibility:** Adapter handles only translation
- ✅ **Testability:** Mock adapters for unit tests
- ✅ **Flexibility:** Adapt multiple classes to same interface
- ✅ **Maintainability:** Changes isolated to adapters

**Architectural Thinking:**

> When you have existing code that doesn't match the interface you need, **DON'T modify the existing code** (violates Open/Closed and breaks other clients). Instead, **create an adapter** that translates between the two interfaces. This is the essence of **making incompatible interfaces work together** without modification.

**Real-World Impact:**

In the embedded sensor example, Adapter Pattern enables:
- Integrate sensors from any vendor without modifying core system
- Uniform interface simplifies application logic
- Easy to add new sensor types (just create new adapter)
- Testable with mock adapters (no real hardware needed)
- Vendor SDK changes isolated to adapter classes

This transforms a rigid, vendor-locked system into a flexible, maintainable architecture.

---

## References

- **Design Principles:** Open/Closed, Dependency Inversion, Single Responsibility, Program to an Interface
- **C++ Features:** Virtual functions, smart pointers, multiple inheritance (class adapter), RAII, concepts
- **Related Patterns:** Decorator, Facade, Bridge, Proxy, Factory
- **Real-World Application:** Device drivers, legacy system integration, third-party library wrappers, protocol adapters

