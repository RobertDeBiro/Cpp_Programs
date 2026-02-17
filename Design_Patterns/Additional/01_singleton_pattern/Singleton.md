# Singleton Pattern - Architectural Analysis

## Pattern Definition

**Singleton Pattern** ensures a class has only one instance, while providing a global point of access to that instance.

## Architectural Problem: Why Singleton Exists

### The Core Challenge

In software systems, certain resources should have **exactly one instance**:

1. **Hardware Resources**: I2C bus controller, SPI manager, GPIO controller
2. **System Resources**: Logger, configuration manager, thread pool
3. **Shared Services**: Cache, database connection pool, device driver

**Without Singleton**, developers face:
- ❌ Accidental multiple instances (resource conflicts)
- ❌ Expensive re-initialization
- ❌ Inconsistent state across instances
- ❌ No coordination between components

**With Singleton**, you get:
- ✅ Guaranteed single instance
- ✅ One-time initialization
- ✅ Shared state (all code sees same data)
- ✅ Global access point

## Real-World Example: Autonomous Robot Hardware Manager

### Scenario: Multi-Module Robot System

You're building an autonomous mobile robot (AMR) with:
- **Motor Controller Module**: Controls wheel motors
- **Sensor Module**: Reads distance sensors, IMU
- **Camera Module**: Processes vision data
- **Navigation Module**: Path planning

All modules need access to hardware buses (I2C, SPI, GPIO).

### BAD ARCHITECTURE: Multiple Hardware Manager Instances

```cpp
// BAD: Each module creates its own hardware manager

class HardwareManager {
public:
    HardwareManager() {
        std::cout << "Initializing I2C bus...\n";
        std::cout << "Initializing SPI bus...\n";
        std::cout << "Configuring GPIO pins...\n";
        // Expensive: 500ms initialization time
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    void setI2CSpeed(int khz) {
        m_i2cSpeed = khz;
    }

    int getI2CSpeed() const {
        return m_i2cSpeed;
    }

private:
    int m_i2cSpeed = 100;  // Default 100kHz
};

// Motor Controller Module
class MotorController {
public:
    MotorController() {
        // Creates its OWN hardware manager!
        hwManager = new HardwareManager();  // 500ms delay
        hwManager->setI2CSpeed(400);        // Set to 400kHz
    }

    void moveForward() {
        // Uses I2C at 400kHz
        std::cout << "Motors: I2C at " << hwManager->getI2CSpeed() << "kHz\n";
    }

private:
    HardwareManager* hwManager;
};

// Sensor Module
class SensorModule {
public:
    SensorModule() {
        // Creates ANOTHER hardware manager!
        hwManager = new HardwareManager();  // Another 500ms delay!
        hwManager->setI2CSpeed(100);        // Set to 100kHz (CONFLICT!)
    }

    void readSensors() {
        // Uses I2C at 100kHz (but MotorController set it to 400kHz!)
        std::cout << "Sensors: I2C at " << hwManager->getI2CSpeed() << "kHz\n";
    }

private:
    HardwareManager* hwManager;
};

// Main application
int main() {
    std::cout << "Robot starting...\n";

    // Creates motor controller (500ms initialization)
    MotorController motors;

    // Creates sensor module (ANOTHER 500ms initialization)
    SensorModule sensors;

    // Total startup time: 1000ms (WASTED TIME!)

    motors.moveForward();    // Thinks I2C is at 400kHz
    sensors.readSensors();   // Thinks I2C is at 100kHz

    // PROBLEM: Two instances with conflicting configurations!
    // HARDWARE CONFLICT: I2C bus can only be at ONE speed!
    // RESULT: Undefined behavior, sensor failures, motor errors
}
```

### Problems with Bad Architecture

| Problem | Impact | Cost |
|---------|--------|------|
| **Multiple Initializations** | 500ms × 2 = 1000ms startup delay | Time waste |
| **Resource Conflicts** | I2C configured to two different speeds | Hardware errors |
| **State Inconsistency** | Each instance has different configuration | Bugs |
| **Memory Waste** | Two instances of same data structures | Memory waste |
| **No Coordination** | Modules can't communicate settings | Conflicts |

### Real Hardware Failure

```
[Hardware] I2C bus initialized at 100kHz
[Hardware] I2C bus reconfigured to 400kHz  ← MotorController
[Hardware] I2C bus reconfigured to 100kHz  ← SensorModule (OVERWRITES!)
[Motor] Sending command at 400kHz... FAIL  ← Wrong speed!
[Sensor] Reading at 100kHz... CORRUPTED    ← Bus in bad state!
[System] CRITICAL ERROR: I2C communication failure
```

## GOOD ARCHITECTURE: Singleton Hardware Manager

```cpp
// GOOD: Single hardware manager instance

class HardwareManager {
public:
    // Delete copy operations (prevent accidental copies)
    HardwareManager(const HardwareManager&) = delete;
    HardwareManager& operator=(const HardwareManager&) = delete;

    // Static method to get THE ONLY instance
    static HardwareManager& getInstance() {
        static HardwareManager instance;  // Created once, thread-safe
        return instance;
    }

    void setI2CSpeed(int khz) {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "[HardwareManager] Setting I2C speed to " << khz << "kHz\n";
        m_i2cSpeed = khz;
    }

    int getI2CSpeed() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_i2cSpeed;
    }

    void initializeMotors() {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "[HardwareManager] Initializing motors on I2C bus\n";
        m_motorsInitialized = true;
    }

    void initializeSensors() {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "[HardwareManager] Initializing sensors on I2C bus\n";
        m_sensorsInitialized = true;
    }

    void printStatus() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "\n=== Hardware Status ===\n";
        std::cout << "I2C Speed: " << m_i2cSpeed << " kHz\n";
        std::cout << "Motors: " << (m_motorsInitialized ? "Ready" : "Not initialized") << "\n";
        std::cout << "Sensors: " << (m_sensorsInitialized ? "Ready" : "Not initialized") << "\n";
        std::cout << "=====================\n\n";
    }

private:
    // Private constructor (only getInstance() can create instance)
    HardwareManager() {
        std::cout << "[HardwareManager] Initializing hardware (ONE TIME ONLY)...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "[HardwareManager] Initialization complete!\n\n";
    }

    ~HardwareManager() {
        std::cout << "\n[HardwareManager] Shutting down hardware...\n";
    }

    int m_i2cSpeed = 100;
    bool m_motorsInitialized = false;
    bool m_sensorsInitialized = false;
    mutable std::mutex m_mutex;
};

// Motor Controller Module
class MotorController {
public:
    void initialize() {
        // Get THE ONLY instance (no construction, instant access)
        HardwareManager& hw = HardwareManager::getInstance();
        hw.setI2CSpeed(400);
        hw.initializeMotors();
    }

    void moveForward() {
        HardwareManager& hw = HardwareManager::getInstance();
        std::cout << "[Motors] Moving forward using I2C at "
                  << hw.getI2CSpeed() << "kHz\n";
    }
};

// Sensor Module
class SensorModule {
public:
    void initialize() {
        // Get THE SAME instance (same configuration!)
        HardwareManager& hw = HardwareManager::getInstance();
        // Sees the 400kHz setting from MotorController!
        hw.initializeSensors();
    }

    void readSensors() {
        HardwareManager& hw = HardwareManager::getInstance();
        std::cout << "[Sensors] Reading sensors using I2C at "
                  << hw.getI2CSpeed() << "kHz\n";
    }
};

// Main application
int main() {
    std::cout << "Robot starting...\n\n";

    MotorController motors;
    SensorModule sensors;

    // Initialize modules (hardware initialized ONCE on first access)
    motors.initialize();   // Triggers hardware initialization (500ms)
    sensors.initialize();  // Uses already-initialized hardware (instant!)

    // Both see same hardware state
    motors.moveForward();
    sensors.readSensors();

    // Verify shared state
    HardwareManager::getInstance().printStatus();

    std::cout << "All modules coordinated through single hardware instance!\n";
}
```

### Output (Good Architecture)

```
Robot starting...

[HardwareManager] Initializing hardware (ONE TIME ONLY)...
[HardwareManager] Initialization complete!

[HardwareManager] Setting I2C speed to 400kHz
[HardwareManager] Initializing motors on I2C bus
[HardwareManager] Initializing sensors on I2C bus
[Motors] Moving forward using I2C at 400kHz
[Sensors] Reading sensors using I2C at 400kHz

=== Hardware Status ===
I2C Speed: 400 kHz
Motors: Ready
Sensors: Ready
=====================

All modules coordinated through single hardware instance!

[HardwareManager] Shutting down hardware...
```

### Benefits Achieved

| Benefit | Before Singleton | After Singleton | Improvement |
|---------|------------------|-----------------|-------------|
| **Initialization Time** | 1000ms (2×500ms) | 500ms (once) | **50% faster** |
| **Memory Usage** | 2 instances | 1 instance | **50% less** |
| **I2C Configuration** | Conflicting (100kHz vs 400kHz) | Consistent (400kHz) | **No conflicts** |
| **Module Coordination** | Impossible | Automatic | **Perfect sync** |
| **Hardware Errors** | Frequent | None | **100% reliable** |

## Architectural Thinking Process

### Step 1: Identify the Need

**Question**: "Should this resource have multiple instances?"

For **HardwareManager**:
- ❌ Multiple I2C bus controllers? NO (hardware has one I2C bus)
- ❌ Multiple configurations? NO (bus has one speed setting)
- ❌ Independent instances? NO (all code must see same state)
- ✅ **Single instance required!**

### Step 2: Consider Alternatives

**Alternative 1: Global Variable**
```cpp
HardwareManager globalHW;  // Global instance

// Problems:
// - Initialized at program start (eager, wasteful)
// - No control over construction
// - Can be copied or modified
// - Not thread-safe
```
❌ **Rejected**: No control, not thread-safe

**Alternative 2: Dependency Injection**
```cpp
class MotorController {
    MotorController(HardwareManager& hw) : m_hw(hw) {}
private:
    HardwareManager& m_hw;
};

// Problems:
// - Every class needs HardwareManager parameter
// - Verbose constructors
// - Can still create multiple instances
// - Burden on client code
```
⚠️ **Better for testing**, but doesn't prevent multiple instances

**Alternative 3: Singleton Pattern**
```cpp
HardwareManager& hw = HardwareManager::getInstance();

// Benefits:
// ✓ Prevents multiple instances (private constructor)
// ✓ Global access (getInstance() available everywhere)
// ✓ Lazy initialization (created on first use)
// ✓ Thread-safe (C++11 static local)
// ✓ Automatic cleanup (destructor called at exit)
```
✅ **Selected**: Best fit for hardware resource

### Step 3: Choose Implementation

**Meyer's Singleton** (C++11 static local):
```cpp
static HardwareManager& getInstance() {
    static HardwareManager instance;  // Thread-safe magic!
    return instance;
}
```

**Why Meyer's Singleton?**
1. **Thread-safe**: C++11 guarantees thread-safe initialization
2. **Simple**: No manual locking or double-checked locking
3. **Lazy**: Created on first use (efficient)
4. **Clean**: No pointers or manual memory management
5. **Standard**: Recommended by C++ experts

### Step 4: Prevent Misuse

**Deleted Copy Operations**:
```cpp
HardwareManager(const HardwareManager&) = delete;
HardwareManager& operator=(const HardwareManager&) = delete;
```

**Why delete copies?**
- Prevents accidental copying: `HardwareManager hw2 = hw1;` ← Compile error!
- Enforces singleton guarantee
- Clear intent to maintainers

## Thread Safety Analysis

### The Problem: Race Conditions

```cpp
// WITHOUT thread safety
static HardwareManager* getInstance() {
    if (instance == nullptr) {      // Thread A checks
                                     // Thread B checks (also nullptr!)
        instance = new HardwareManager();  // Thread A creates
        instance = new HardwareManager();  // Thread B creates (LEAK!)
    }
    return instance;
}
```

**Problem**: Two threads can create two instances!

### Solution 1: Meyer's Singleton (Recommended)

```cpp
static HardwareManager& getInstance() {
    static HardwareManager instance;  // C++11: Thread-safe!
    return instance;
}
```

**C++11 Standard (§6.7.4)**: If multiple threads attempt to initialize the same static local variable concurrently, initialization occurs exactly once.

**Compiler generates** (conceptually):
```cpp
static bool initialized = false;
static std::mutex init_mutex;
static char buffer[sizeof(HardwareManager)];

if (!initialized) {
    std::lock_guard<std::mutex> lock(init_mutex);
    if (!initialized) {
        new (buffer) HardwareManager();
        initialized = true;
    }
}
return *reinterpret_cast<HardwareManager*>(buffer);
```

### Solution 2: Call Once (Manual)

```cpp
class HardwareManager {
    static HardwareManager* instance;
    static std::once_flag initFlag;

public:
    static HardwareManager& getInstance() {
        std::call_once(initFlag, []() {
            instance = new HardwareManager();
        });
        return *instance;
    }
};
```

✅ **Thread-safe**, but more verbose than Meyer's Singleton

## Testing Challenges and Solutions

### Challenge: Hard to Test

**Problem**: Singleton creates tight coupling and global state

```cpp
// Hard to test!
void processData() {
    HardwareManager& hw = HardwareManager::getInstance();
    hw.initializeI2C(0);  // Hardcoded dependency!
}
```

**Testing issues**:
- Can't inject mock
- State persists between tests
- Tests affect each other

### Solution 1: Reset Method (Simple)

```cpp
class HardwareManager {
public:
    static void resetForTesting() {
        getInstance().m_i2cSpeed = 100;
        getInstance().m_motorsInitialized = false;
        getInstance().m_sensorsInitialized = false;
    }
};

// In tests:
TEST(RobotTest, MotorInitialization) {
    HardwareManager::resetForTesting();  // Clean state
    // ... test code ...
}
```

### Solution 2: Dependency Injection (Better)

```cpp
// Interface for testing
class IHardwareManager {
public:
    virtual ~IHardwareManager() = default;
    virtual void initializeI2C(int bus) = 0;
    virtual void setI2CSpeed(int khz) = 0;
};

// Real implementation
class HardwareManager : public IHardwareManager {
    // ... singleton implementation ...
};

// Mock for testing
class MockHardwareManager : public IHardwareManager {
    // ... mock implementation ...
};

// Code uses interface
class MotorController {
public:
    explicit MotorController(IHardwareManager& hw) : m_hw(hw) {}

    void initialize() {
        m_hw.initializeI2C(0);
    }

private:
    IHardwareManager& m_hw;
};

// Production: Use singleton
MotorController motors(HardwareManager::getInstance());

// Testing: Inject mock
MockHardwareManager mockHW;
MotorController motors(mockHW);
```

## When NOT to Use Singleton

### Anti-Pattern: Singleton Overuse

**Bad**: Using Singleton for convenience
```cpp
class DataProcessor {  // Doesn't need to be Singleton!
public:
    static DataProcessor& getInstance() { /* ... */ }
    void process(Data d) { /* ... */ }
};
```

**Why bad?**
- Multiple processors might be useful
- Hard to test
- Artificial limitation

**Better**: Regular class with dependency injection
```cpp
class DataProcessor {
public:
    void process(Data d) { /* ... */ }
};

// Create as many as needed
DataProcessor processor1;
DataProcessor processor2;
```

### Singleton Checklist

Use Singleton ONLY if:
- ✅ Resource MUST have exactly one instance (hardware, logger)
- ✅ Global access is genuinely needed
- ✅ Instance is expensive to create
- ✅ Multiple instances would cause problems

Don't use Singleton if:
- ❌ Multiple instances are acceptable
- ❌ Using it just for "convenience"
- ❌ Can use dependency injection instead
- ❌ Might need different instances for testing

## Singleton Variations

### 1. Lazy Singleton (Meyer's) ✅ **Recommended**
```cpp
static Singleton& getInstance() {
    static Singleton instance;
    return instance;
}
```
- Created on first use
- Thread-safe (C++11+)
- Simple

### 2. Eager Singleton
```cpp
class Singleton {
    static Singleton instance;  // Created at startup
public:
    static Singleton& getInstance() { return instance; }
};
Singleton Singleton::instance;  // Definition
```
- Created at program start
- Thread-safe
- May waste resources

### 3. Leaky Singleton (Avoid)
```cpp
static Singleton* getInstance() {
    static Singleton* instance = new Singleton();
    return instance;  // Never deleted (memory leak)
}
```
- Used to avoid destruction order issues
- Memory leak (intentional)
- ⚠️ **Avoid**: Use Meyer's Singleton instead

## Design Principles

### 1. Single Responsibility Principle
**Class has one reason to change**: Managing its single instance

### 2. Information Hiding
**Private constructor**: Only class controls instantiation

### 3. Global Access
**Static method**: Available everywhere (use carefully!)

## Summary

### Singleton Solves
✅ Multiple instance prevention
✅ Expensive re-initialization
✅ Resource conflicts
✅ State inconsistency
✅ Coordination problems

### Key Insights
1. **Use sparingly**: Only when truly needed
2. **Meyer's Singleton**: Preferred in modern C++
3. **Thread safety**: Built-in with C++11 static locals
4. **Testing**: Consider dependency injection for testability
5. **Hardware/Resources**: Perfect use case

### Architectural Impact

**Before Singleton**:
- Developers can accidentally create multiple instances
- No guarantee of coordination
- Resource conflicts possible
- Expensive repeated initialization

**After Singleton**:
- Single instance guaranteed by design
- All code coordinated through same instance
- No resource conflicts
- Initialization once, used everywhere
- Clear architectural intent

The Singleton pattern is a powerful tool when used correctly: it ensures critical resources have exactly one instance, provides global coordination, and prevents expensive re-initialization. In robotics and embedded systems, where hardware resources MUST be managed carefully, Singleton is often the right architectural choice.
