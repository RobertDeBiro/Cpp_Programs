# Iterator and Composite Patterns - Comprehensive Analysis

## Table of Contents

1. [Overview](#overview)
2. [Iterator Pattern](#iterator-pattern)
   - [Pattern Definition](#iterator-pattern-definition)
   - [The Problem: Exposing Collection Implementation](#the-problem-exposing-collection-implementation)
   - [Real-World Example: Embedded Sensor Array Management](#real-world-example-embedded-sensor-array-management)
   - [Design Principles: Single Responsibility](#design-principles-single-responsibility)
   - [The Solution: Iterator Pattern](#the-solution-iterator-pattern)
   - [Benefits and Trade-offs](#iterator-benefits-and-trade-offs)
3. [Composite Pattern](#composite-pattern)
   - [Pattern Definition](#composite-pattern-definition)
   - [The Problem: Treating Leaves and Composites Differently](#the-problem-treating-leaves-and-composites-differently)
   - [Real-World Example: Embedded Device Hierarchy](#real-world-example-embedded-device-hierarchy)
   - [Design Principles: Uniform Treatment](#design-principles-uniform-treatment)
   - [The Solution: Composite Pattern](#the-solution-composite-pattern)
   - [Benefits and Trade-offs](#composite-benefits-and-trade-offs)
4. [Patterns Working Together](#patterns-working-together)
5. [C++ Specific Considerations](#c-specific-considerations)
6. [Pattern Relationships](#pattern-relationships)

---

## Overview

This chapter introduces TWO powerful structural patterns that often work together:

**Iterator Pattern**: Provides a way to access elements of a collection sequentially without exposing its underlying representation. It separates the responsibility of collection traversal from the collection itself.

**Composite Pattern**: Composes objects into tree structures to represent part-whole hierarchies. It allows you to treat individual objects and compositions of objects uniformly.

Both patterns promote loose coupling and adhere to the Single Responsibility Principle. They're particularly powerful when combined, as we'll see in embedded systems applications.

---

## Iterator Pattern

### Iterator Pattern Definition

**Iterator Pattern** provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation.

**Key Intent:** Separate the responsibility of traversing a collection from the collection implementation itself.

**Also Known As:** Cursor

**Core Concept:** The iterator encapsulates the traversal logic, allowing the same collection to be traversed in different ways and allowing different collections to be traversed through a uniform interface.

---

## The Problem: Exposing Collection Implementation

### Bad Architecture Example: Direct Collection Exposure

```cpp
// BAD: Different menu implementations expose their internal structures

class PancakeHouseMenu {
private:
    std::vector<MenuItem> m_items;  // Uses vector

public:
    // PROBLEM: Exposes internal representation
    std::vector<MenuItem>& getItems() { return m_items; }
};

class DinerMenu {
private:
    std::array<MenuItem, MAX_SIZE> m_items;  // Uses array
    int m_numberOfItems;

public:
    // PROBLEM: Exposes internal representation (different from PancakeHouse!)
    MenuItem* getItems() { return m_items.data(); }
    int getCount() const { return m_numberOfItems; }
};

class CafeMenu {
private:
    std::map<std::string, MenuItem> m_items;  // Uses map

public:
    // PROBLEM: Yet another interface to expose internal representation
    std::map<std::string, MenuItem>& getItems() { return m_items; }
};

// Client code must know about all implementations
class Waitress {
private:
    PancakeHouseMenu* m_pancakeMenu;
    DinerMenu* m_dinerMenu;
    CafeMenu* m_cafeMenu;

public:
    void printMenu() {
        // PROBLEM: Different code for each menu type

        // PancakeHouse - iterate vector
        auto& pancakeItems = m_pancakeMenu->getItems();
        for (const auto& item : pancakeItems) {
            printItem(item);
        }

        // Diner - iterate array
        MenuItem* dinerItems = m_dinerMenu->getItems();
        int count = m_dinerMenu->getCount();
        for (int i = 0; i < count; ++i) {
            printItem(dinerItems[i]);
        }

        // Cafe - iterate map
        auto& cafeItems = m_cafeMenu->getItems();
        for (const auto& [name, item] : cafeItems) {
            printItem(item);
        }
    }

    void printItem(const MenuItem& item) {
        std::cout << item.getName() << ": $" << item.getPrice() << "\n";
    }
};

// PROBLEMS:
// 1. Client depends on concrete collection types (vector, array, map)
// 2. Cannot change collection implementation without breaking clients
// 3. Client has multiple responsibilities: knowing menu types AND traversal logic
// 4. Adding new menu type requires modifying client code
// 5. Internal representation exposed - breaks encapsulation
// 6. Cannot provide alternative traversal methods
```

### Pain Points

1. **Tight Coupling to Implementation**
   - Client code depends on specific collection types
   - `Waitress` must know vector, array, and map interfaces
   - Cannot swap implementations without breaking code
   - Violates "Program to interfaces, not implementations"

2. **Broken Encapsulation**
   - `getItems()` exposes internal data structures
   - Clients can modify internal state directly
   - No control over how collection is accessed
   - Implementation details leak into client code

3. **Multiple Responsibilities**
   - Collection manages storage AND traversal logic
   - Client manages menu logic AND knows traversal details
   - Violates Single Responsibility Principle
   - Changes to traversal affect multiple classes

4. **Code Duplication**
   - Different iteration code for each collection type
   - Same traversal patterns repeated for each menu
   - Adding new operation requires duplicating iteration logic
   - Error-prone when maintaining multiple traversal patterns

5. **Inflexibility**
   - Cannot change collection type without breaking clients
   - Cannot add new collection types easily
   - Cannot provide alternative traversal methods
   - Difficult to support filtering or specialized traversals

6. **Testing Nightmare**
   - Must test with all collection types
   - Cannot mock collection easily
   - Traversal logic scattered across codebase
   - Integration tests required instead of unit tests

---

## Real-World Example: Embedded Sensor Array Management

### The Problem in Embedded Systems

Imagine you're building a sophisticated sensor management system for an industrial IoT device. Your system needs to collect data from various sensor types:

- **Temperature sensors**: Stored in a fixed-size array (known sensor count at compile time)
- **Pressure sensors**: Stored in a dynamic vector (variable count based on configuration)
- **Flow sensors**: Stored in a map indexed by sensor ID (sparse sensor network)

```cpp
// BAD: Embedded sensor system WITHOUT Iterator Pattern

class TemperatureSensorArray {
private:
    static constexpr size_t MAX_SENSORS = 16;
    Sensor m_sensors[MAX_SENSORS];
    size_t m_count;

public:
    // Exposes internal array
    Sensor* getSensors() { return m_sensors; }
    size_t getCount() const { return m_count; }
};

class PressureSensorVector {
private:
    std::vector<Sensor> m_sensors;

public:
    // Exposes internal vector
    std::vector<Sensor>& getSensors() { return m_sensors; }
};

class FlowSensorMap {
private:
    std::map<uint32_t, Sensor> m_sensors;  // ID -> Sensor

public:
    // Exposes internal map
    std::map<uint32_t, Sensor>& getSensors() { return m_sensors; }
};

class SensorDataCollector {
public:
    void collectAllReadings(TemperatureSensorArray& tempSensors,
                           PressureSensorVector& pressureSensors,
                           FlowSensorMap& flowSensors) {
        // Different code for each sensor type!

        // Temperature sensors - array iteration
        for (size_t i = 0; i < tempSensors.getCount(); ++i) {
            Sensor* sensor = &tempSensors.getSensors()[i];
            readSensor(sensor);
        }

        // Pressure sensors - vector iteration
        for (auto& sensor : pressureSensors.getSensors()) {
            readSensor(&sensor);
        }

        // Flow sensors - map iteration
        for (auto& [id, sensor] : flowSensors.getSensors()) {
            readSensor(&sensor);
        }
    }

    void readSensor(Sensor* sensor) {
        sensor->read();
        processReading(sensor->getValue());
    }

    void processReading(double value) {
        // Process sensor reading
    }
};

// PROBLEMS in embedded context:
// 1. Cannot change storage without breaking data collection code
// 2. Adding new sensor type requires modifying collector
// 3. Cannot easily mock sensors for testing
// 4. Tight coupling prevents sensor abstraction layers
// 5. Difficult to support different traversal orders (priority-based, etc.)
// 6. Memory layout exposed - breaks memory-mapped I/O abstraction
```

### Why This Hurts in Embedded Systems

1. **Hardware Changes Break Code**
   - Sensor array size changes require code modifications
   - Different hardware configurations need different code paths
   - Cannot support multiple hardware variants with same code

2. **Memory Management Exposed**
   - Flash vs RAM sensor storage exposed to clients
   - Memory-mapped sensor registers exposed
   - Cannot abstract DMA-based sensor reading

3. **Real-Time Constraints**
   - Cannot prioritize critical sensors
   - Cannot implement time-bounded iteration
   - Fixed traversal order regardless of urgency

4. **Testing Difficulties**
   - Cannot unit test without real hardware
   - Difficult to simulate sensor failures
   - Integration testing required for simple logic

5. **Firmware Updates**
   - Changing sensor layout breaks protocol
   - Cannot support backward compatibility
   - Firmware updates risky due to tight coupling

---

## Design Principles: Single Responsibility

### Single Responsibility Principle

**"A class should have only one reason to change."**

The Iterator Pattern embodies this principle by separating two responsibilities:

1. **Collection Responsibility**: Managing the collection of objects
   - Add/remove elements
   - Store elements efficiently
   - Maintain collection invariants

2. **Traversal Responsibility**: Providing access to elements
   - Sequential access
   - Filtering
   - Alternative orderings

Without the Iterator Pattern, collections have TWO reasons to change:
- Their storage strategy changes
- The way clients want to traverse them changes

With the Iterator Pattern, these responsibilities are separated, making both the collection and the traversal logic easier to maintain and extend.

### Programming to Interfaces, Not Implementations

The Iterator Pattern allows clients to work with an Iterator interface without knowing:
- What type of collection is being iterated
- How the collection stores its elements
- Whether the collection is in-memory, on disk, or remote

This is "programming to interfaces" in action.

---

## The Solution: Iterator Pattern

### Structure

```
┌─────────────────┐
│   <<interface>> │
│    Iterator     │
├─────────────────┤
│ + hasNext()     │
│ + next()        │
└─────────────────┘
         △
         │ implements
         │
┌────────┴────────┐
│  ConcreteIter   │
│     ator        │
├─────────────────┤
│ + hasNext()     │
│ + next()        │
└─────────────────┘

┌─────────────────┐          ┌─────────────────┐
│  <<interface>>  │          │     Client      │
│   Aggregate     │◄─────────│   (Waitress)    │
├─────────────────┤          └─────────────────┘
│ +createIterator │
└─────────────────┘
         △
         │ implements
         │
┌────────┴────────┐
│  ConcreteAggr   │
│     egate       │
├─────────────────┤
│ +createIterator │──────creates──────┐
│ +getItem()      │                   │
└─────────────────┘                   ▼
                              ┌─────────────────┐
                              │  ConcreteIter   │
                              │     ator        │
                              └─────────────────┘
```

### Implementation

```cpp
// Iterator interface - uniform traversal
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual MenuItem* next() = 0;
};

// Aggregate interface - factory for iterators
class Menu {
public:
    virtual ~Menu() = default;
    virtual std::unique_ptr<Iterator> createIterator() = 0;
};

// Concrete menu - hides array implementation
class DinerMenu : public Menu {
private:
    std::array<std::unique_ptr<MenuItem>, MAX_ITEMS> m_items;
    size_t m_count{0};

    // Nested iterator - knows how to traverse array
    class DinerMenuIterator : public Iterator {
    private:
        const std::array<std::unique_ptr<MenuItem>, MAX_ITEMS>& m_items;
        size_t m_position{0};

    public:
        explicit DinerMenuIterator(const std::array<std::unique_ptr<MenuItem>, MAX_ITEMS>& items)
            : m_items(items) {}

        bool hasNext() const override {
            return m_position < MAX_ITEMS && m_items[m_position] != nullptr;
        }

        MenuItem* next() override {
            if (hasNext()) {
                return m_items[m_position++].get();
            }
            return nullptr;
        }
    };

public:
    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<DinerMenuIterator>(m_items);
    }

    void addItem(const std::string& name, const std::string& desc,
                 bool vegetarian, double price) {
        if (m_count >= MAX_ITEMS) {
            std::cerr << "Menu is full!\n";
            return;
        }
        m_items[m_count++] = std::make_unique<MenuItem>(name, desc, vegetarian, price);
    }
};

// Concrete menu - hides vector implementation
class PancakeHouseMenu : public Menu {
private:
    std::vector<std::unique_ptr<MenuItem>> m_items;

    // Nested iterator - knows how to traverse vector
    class PancakeMenuIterator : public Iterator {
    private:
        const std::vector<std::unique_ptr<MenuItem>>& m_items;
        size_t m_position{0};

    public:
        explicit PancakeMenuIterator(const std::vector<std::unique_ptr<MenuItem>>& items)
            : m_items(items) {}

        bool hasNext() const override {
            return m_position < m_items.size();
        }

        MenuItem* next() override {
            if (hasNext()) {
                return m_items[m_position++].get();
            }
            return nullptr;
        }
    };

public:
    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<PancakeMenuIterator>(m_items);
    }

    void addItem(const std::string& name, const std::string& desc,
                 bool vegetarian, double price) {
        m_items.push_back(std::make_unique<MenuItem>(name, desc, vegetarian, price));
    }
};

// Client - works with Iterator interface only
class Waitress {
private:
    std::vector<Menu*> m_menus;

    void printMenu(Iterator* iterator) const {
        while (iterator->hasNext()) {
            MenuItem* item = iterator->next();
            if (item != nullptr) {
                item->print();
            }
        }
    }

public:
    explicit Waitress(std::vector<Menu*> menus) : m_menus(std::move(menus)) {}

    void printMenu() const {
        for (auto* menu : m_menus) {
            auto iterator = menu->createIterator();
            printMenu(iterator.get());
        }
    }

    void printVegetarianMenu() const {
        for (auto* menu : m_menus) {
            auto iterator = menu->createIterator();
            while (iterator->hasNext()) {
                MenuItem* item = iterator->next();
                if (item != nullptr && item->isVegetarian()) {
                    item->print();
                }
            }
        }
    }
};
```

### Key Architectural Decisions

1. **Iterator Interface**
   - `hasNext()`: Tests if more elements exist
   - `next()`: Returns next element and advances position
   - Simple, focused interface

2. **Factory Method Pattern**
   - `createIterator()` is a factory method
   - Each menu creates its specific iterator type
   - Clients don't know concrete iterator classes

3. **Nested Iterator Classes**
   - Iterators are nested within their aggregate classes
   - Encapsulation: Iterator details hidden from clients
   - Access: Iterator can access aggregate's private members

4. **Separation of Concerns**
   - Menu: Manages collection
   - Iterator: Manages traversal
   - Waitress: Uses both through interfaces

---

## Real-World Example: Embedded Sensor Array Management (Solved)

### Iterator Pattern Applied to Embedded Systems

Now let's solve the sensor management problem using the Iterator Pattern:

```cpp
// Sensor iterator interface
class SensorIterator {
public:
    virtual ~SensorIterator() = default;
    virtual bool hasNext() const = 0;
    virtual Sensor* next() = 0;
};

// Sensor collection interface
class SensorCollection {
public:
    virtual ~SensorCollection() = default;
    virtual std::unique_ptr<SensorIterator> createIterator() = 0;
    virtual size_t getCount() const = 0;
};

// Temperature sensors - fixed array (flash memory, known at compile time)
class TemperatureSensorArray : public SensorCollection {
private:
    static constexpr size_t MAX_SENSORS = 16;
    Sensor m_sensors[MAX_SENSORS];  // Array in flash
    size_t m_count;

    class ArrayIterator : public SensorIterator {
    private:
        Sensor* m_sensors;
        size_t m_maxCount;
        size_t m_position{0};

    public:
        ArrayIterator(Sensor* sensors, size_t maxCount)
            : m_sensors(sensors), m_maxCount(maxCount) {}

        bool hasNext() const override {
            return m_position < m_maxCount && m_sensors[m_position].isValid();
        }

        Sensor* next() override {
            if (hasNext()) {
                return &m_sensors[m_position++];
            }
            return nullptr;
        }
    };

public:
    std::unique_ptr<SensorIterator> createIterator() override {
        return std::make_unique<ArrayIterator>(m_sensors, MAX_SENSORS);
    }

    size_t getCount() const override { return m_count; }
};

// Pressure sensors - dynamic vector (RAM, configured at runtime)
class PressureSensorVector : public SensorCollection {
private:
    std::vector<Sensor> m_sensors;  // Dynamic RAM allocation

    class VectorIterator : public SensorIterator {
    private:
        std::vector<Sensor>& m_sensors;
        size_t m_position{0};

    public:
        explicit VectorIterator(std::vector<Sensor>& sensors)
            : m_sensors(sensors) {}

        bool hasNext() const override {
            return m_position < m_sensors.size();
        }

        Sensor* next() override {
            if (hasNext()) {
                return &m_sensors[m_position++];
            }
            return nullptr;
        }
    };

public:
    std::unique_ptr<SensorIterator> createIterator() override {
        return std::make_unique<VectorIterator>(m_sensors);
    }

    size_t getCount() const override { return m_sensors.size(); }
};

// Flow sensors - memory-mapped registers (hardware addresses)
class FlowSensorRegisters : public SensorCollection {
private:
    std::map<uint32_t, Sensor> m_sensors;  // Register address -> Sensor

    class RegisterIterator : public SensorIterator {
    private:
        std::vector<Sensor*> m_sensorPtrs;  // Cache for iteration
        size_t m_position{0};

    public:
        explicit RegisterIterator(std::map<uint32_t, Sensor>& sensors) {
            // Convert map to vector for efficient iteration
            m_sensorPtrs.reserve(sensors.size());
            for (auto& [addr, sensor] : sensors) {
                m_sensorPtrs.push_back(&sensor);
            }
        }

        bool hasNext() const override {
            return m_position < m_sensorPtrs.size();
        }

        Sensor* next() override {
            if (hasNext()) {
                return m_sensorPtrs[m_position++];
            }
            return nullptr;
        }
    };

public:
    std::unique_ptr<SensorIterator> createIterator() override {
        return std::make_unique<RegisterIterator>(m_sensors);
    }

    size_t getCount() const override { return m_sensors.size(); }
};

// Data collector - uniform sensor access through iterators
class SensorDataCollector {
private:
    std::vector<SensorCollection*> m_collections;

    void readSensor(Sensor* sensor) {
        if (sensor != nullptr) {
            sensor->read();
            processReading(sensor->getValue());
        }
    }

    void processReading(double value) {
        // Process sensor reading
        logReading(value);
        checkThresholds(value);
    }

public:
    explicit SensorDataCollector(std::vector<SensorCollection*> collections)
        : m_collections(std::move(collections)) {}

    // Collect all readings - uniform code for all sensor types!
    void collectAllReadings() {
        for (auto* collection : m_collections) {
            auto iterator = collection->createIterator();
            while (iterator->hasNext()) {
                Sensor* sensor = iterator->next();
                readSensor(sensor);
            }
        }
    }

    // Collect readings with timeout (real-time constraint)
    void collectReadingsWithTimeout(uint32_t timeoutMs) {
        uint32_t startTime = getSystemTimeMs();

        for (auto* collection : m_collections) {
            auto iterator = collection->createIterator();
            while (iterator->hasNext()) {
                if (getSystemTimeMs() - startTime > timeoutMs) {
                    logWarning("Sensor reading timeout");
                    return;  // Time-bounded iteration
                }

                Sensor* sensor = iterator->next();
                readSensor(sensor);
            }
        }
    }

    // Collect only critical sensors first
    void collectPriorityReadings() {
        for (auto* collection : m_collections) {
            // First pass: critical sensors
            auto iterator = collection->createIterator();
            while (iterator->hasNext()) {
                Sensor* sensor = iterator->next();
                if (sensor != nullptr && sensor->isCritical()) {
                    readSensor(sensor);
                }
            }

            // Second pass: non-critical sensors
            iterator = collection->createIterator();
            while (iterator->hasNext()) {
                Sensor* sensor = iterator->next();
                if (sensor != nullptr && !sensor->isCritical()) {
                    readSensor(sensor);
                }
            }
        }
    }

    // Count active sensors
    size_t countActiveSensors() const {
        size_t count = 0;
        for (auto* collection : m_collections) {
            auto iterator = collection->createIterator();
            while (iterator->hasNext()) {
                Sensor* sensor = iterator->next();
                if (sensor != nullptr && sensor->isActive()) {
                    ++count;
                }
            }
        }
        return count;
    }
};
```

### Benefits in Embedded Context

1. **Hardware Abstraction**
   - Sensor storage details hidden (flash, RAM, registers)
   - Memory-mapped I/O abstracted
   - DMA vs polling hidden from client

2. **Flexible Configuration**
   - Support multiple hardware variants
   - Runtime sensor configuration
   - Hot-plug sensor support

3. **Real-Time Support**
   - Time-bounded iteration
   - Priority-based traversal
   - Interrupt-safe iteration patterns

4. **Testability**
   - Mock sensor collections for unit tests
   - Simulate sensor failures
   - Test data collection without hardware

5. **Maintainability**
   - Adding new sensor types easy
   - Storage strategy changes isolated
   - Traversal logic reusable

---

## Iterator Benefits and Trade-offs

### Benefits

1. **Encapsulation**
   - Internal collection structure hidden
   - Clients can't directly modify collection
   - Implementation can change without breaking clients

2. **Single Responsibility**
   - Collection manages storage
   - Iterator manages traversal
   - Each class has one reason to change

3. **Uniform Interface**
   - All collections accessed the same way
   - Client code simpler and cleaner
   - Polymorphic iteration

4. **Multiple Traversals**
   - Multiple iterators on same collection
   - Different traversal strategies
   - Concurrent iteration support

5. **Open/Closed Principle**
   - Add new collection types without modifying clients
   - Add new iterator types without modifying collections
   - Extension without modification

### Trade-offs

1. **Added Complexity**
   - More classes: Iterator, ConcreteIterator for each collection
   - Indirection layer adds overhead
   - Learning curve for simple cases

2. **Performance Overhead**
   - Virtual function calls for each iteration
   - Heap allocation for iterator objects
   - May be slower than direct access

3. **Memory Overhead**
   - Iterator objects consume memory
   - May need to cache collection references
   - Not ideal for extremely memory-constrained systems

4. **Interface Limitations**
   - Simple interface (hasNext/next) may not fit all cases
   - Bidirectional iteration needs additional methods
   - Random access difficult to support generically

5. **C++ STL Competition**
   - STL already provides iterators
   - Custom iterators don't integrate with STL algorithms
   - May be better to use STL containers when possible

---

## Composite Pattern

### Composite Pattern Definition

**Composite Pattern** allows you to compose objects into tree structures to represent part-whole hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly.

**Key Intent:** Build tree structures and treat leaf nodes and composite nodes the same way.

**Also Known As:** Part-Whole Hierarchy

**Core Concept:** A component can be either a leaf (individual object) or a composite (container of components). Both implement the same interface, allowing uniform treatment.

---

## The Problem: Treating Leaves and Composites Differently

### Bad Architecture Example: Explicit Leaf vs Composite Handling

```cpp
// BAD: Separate classes for items and containers

class MenuItem {
private:
    std::string m_name;
    std::string m_description;
    bool m_vegetarian;
    double m_price;

public:
    void print() const {
        std::cout << m_name << ", $" << m_price << "\n";
    }

    bool isVegetarian() const { return m_vegetarian; }
};

class Menu {
private:
    std::vector<MenuItem> m_items;
    std::string m_name;

public:
    void addItem(const MenuItem& item) {
        m_items.push_back(item);
    }

    void print() const {
        std::cout << "\n" << m_name << "\n";
        for (const auto& item : m_items) {
            item.print();
        }
    }
};

// PROBLEM: Cannot nest menus - no support for submenus!
// PROBLEM: Client must know whether it's dealing with Menu or MenuItem
// PROBLEM: Cannot treat individual items and groups uniformly

class Waitress {
public:
    void printMenu(Menu& menu) {
        menu.print();  // Different method for Menu
    }

    void printItem(MenuItem& item) {
        item.print();  // Different method for MenuItem
    }

    // PROBLEM: What if we want a dessert submenu within the diner menu?
    // Cannot represent this hierarchy!
};

// PROBLEMS:
// 1. Cannot create hierarchical structures (menu in menu)
// 2. Client must know if it's dealing with leaf or composite
// 3. Different code paths for individual items vs menus
// 4. Cannot treat uniformly - violates polymorphism
// 5. Adding new levels requires new classes and client changes
```

### Pain Points

1. **No Hierarchical Structure**
   - Cannot nest menus within menus
   - Flat structure only
   - Real-world hierarchies not representable

2. **Type-Specific Client Code**
   - Client must know `MenuItem` vs `Menu`
   - Different method calls for each type
   - No polymorphic treatment

3. **Limited Extensibility**
   - Adding new component types requires client changes
   - Cannot create arbitrary tree depths
   - Fixed structure, not flexible

4. **Code Duplication**
   - Similar operations (`print`) implemented separately
   - Traversal logic duplicated for each level
   - Common functionality not shared

5. **Maintenance Burden**
   - Changes to operations require updating multiple classes
   - Adding new operations requires modifying both leaf and composite
   - No uniform interface to program against

---

## Real-World Example: Embedded Device Hierarchy

### The Problem in Embedded Systems

Consider an industrial control system with a hierarchical device structure:

```
System
├── Power Subsystem
│   ├── Main Power Supply
│   ├── Battery Backup
│   └── Voltage Regulator Subsystem
│       ├── 5V Regulator
│       ├── 3.3V Regulator
│       └── 1.8V Regulator
├── Sensor Subsystem
│   ├── Temperature Sensor
│   ├── Pressure Sensor
│   └── Environmental Sensors
│       ├── Humidity Sensor
│       └── Air Quality Sensor
└── Communication Subsystem
    ├── Ethernet Controller
    ├── WiFi Module
    └── Serial Interfaces
        ├── UART
        ├── SPI
        └── I2C
```

```cpp
// BAD: Without Composite Pattern

class Device {
protected:
    std::string m_name;
    DeviceState m_state;

public:
    virtual void initialize() = 0;
    virtual void shutdown() = 0;
    virtual DeviceState getState() const { return m_state; }
    virtual void printStatus() const = 0;
};

class PowerSupply : public Device {
public:
    void initialize() override {
        // Initialize power supply
        m_state = DeviceState::RUNNING;
    }

    void shutdown() override {
        m_state = DeviceState::SHUTDOWN;
    }

    void printStatus() const override {
        std::cout << "Power Supply: " << stateToString(m_state) << "\n";
    }
};

class TemperatureSensor : public Device {
public:
    void initialize() override {
        // Initialize sensor
        m_state = DeviceState::RUNNING;
    }

    void shutdown() override {
        m_state = DeviceState::SHUTDOWN;
    }

    void printStatus() const override {
        std::cout << "Temperature Sensor: " << stateToString(m_state) << "\n";
    }
};

// PROBLEM: How to represent subsystems that contain other devices?
// Need a separate DeviceGroup class...

class DeviceGroup {
private:
    std::vector<Device*> m_devices;
    std::string m_name;

public:
    void addDevice(Device* device) {
        m_devices.push_back(device);
    }

    // PROBLEM: Different interface than Device!
    void initializeAll() {
        for (auto* device : m_devices) {
            device->initialize();
        }
    }

    void shutdownAll() {
        for (auto* device : m_devices) {
            device->shutdown();
        }
    }

    void printAllStatus() const {
        std::cout << "Group: " << m_name << "\n";
        for (auto* device : m_devices) {
            device->printStatus();
        }
    }

    // PROBLEM: Cannot nest DeviceGroups!
    // PROBLEM: Cannot treat DeviceGroup like a Device!
};

// System control
class SystemController {
public:
    void initializeSystem(PowerSupply& power, TemperatureSensor& tempSensor,
                         DeviceGroup& sensorGroup, DeviceGroup& commGroup) {
        // PROBLEM: Different code for each type!
        power.initialize();
        tempSensor.initialize();
        sensorGroup.initializeAll();
        commGroup.initializeAll();

        // PROBLEM: What if sensorGroup contains another DeviceGroup?
        // Cannot handle nested structures!
    }

    void printSystemStatus(PowerSupply& power, TemperatureSensor& tempSensor,
                           DeviceGroup& sensorGroup, DeviceGroup& commGroup) {
        // PROBLEM: Must know all device types and groups!
        power.printStatus();
        tempSensor.printStatus();
        sensorGroup.printAllStatus();
        commGroup.printAllStatus();
    }
};

// PROBLEMS in embedded context:
// 1. Cannot represent hierarchical device trees
// 2. Must treat individual devices and subsystems differently
// 3. Cannot nest subsystems arbitrarily
// 4. Adding hierarchy levels requires code changes
// 5. Cannot initialize/shutdown entire subsystem uniformly
// 6. Difficult to model real hardware organization
```

### Why This Hurts in Embedded Systems

1. **Hardware Organization Mismatch**
   - Real hardware is hierarchical (boards → modules → chips → peripherals)
   - Code structure doesn't match hardware structure
   - Mental model mismatch makes code confusing

2. **Power Management Nightmare**
   - Cannot power down entire subsystem uniformly
   - Must manually track all devices in subsystem
   - Error-prone when adding/removing devices

3. **Initialization Sequence Complex**
   - Cannot initialize subsystem as unit
   - Must manually order device initialization
   - Dependencies between devices difficult to manage

4. **Status Reporting Difficult**
   - Cannot get subsystem status uniformly
   - Must aggregate status manually
   - No hierarchical view of system health

5. **Configuration Management**
   - Cannot configure subsystem as unit
   - Individual device configuration scattered
   - Difficult to save/restore subsystem state

---

## Design Principles: Uniform Treatment

### Composite Principle

**"Treat individual objects and compositions of objects uniformly."**

The Composite Pattern allows you to:
- Ignore the difference between compositions of objects and individual objects
- Write code that works with complex tree structures
- Apply operations recursively through the tree structure

### Single Responsibility Applied

Each component has one job:
- **Leaf**: Implements behavior for primitive objects
- **Composite**: Implements behavior for components having children
- **Component**: Defines interface for all objects in composition

### Trade-off: Safety vs Transparency

The Composite Pattern makes a trade-off:

**Transparency** (chosen by Composite Pattern):
- Leaf and Composite share same interface
- Client treats them uniformly (transparent)
- Some operations don't make sense for some components (e.g., `add()` on leaf)
- Throws exceptions for unsupported operations

**Safety** (alternative approach):
- Leaf and Composite have different interfaces
- Compile-time safety (can't call `add()` on leaf)
- Client must know type (not transparent)
- Less uniform, more type checking

The Composite Pattern chooses transparency over safety, believing the uniform interface is more valuable than compile-time type safety for unsupported operations.

---

## The Solution: Composite Pattern

### Structure

```
┌─────────────────────────┐
│      Component          │
│   (MenuComponent)       │
├─────────────────────────┤
│ + operation()           │
│ + add(Component)        │
│ + remove(Component)     │
│ + getChild(int)         │
└─────────────────────────┘
           △
           │
      ┌────┴────┐
      │         │
┌─────┴─────┐  ┌┴──────────────────┐
│   Leaf    │  │    Composite      │
│(MenuItem) │  │     (Menu)        │
├───────────┤  ├───────────────────┤
│+operation │  │+ operation()      │
└───────────┘  │+ add(Component)   │
               │+ remove(Component)│
               │+ getChild(int)    │
               └───────────────────┘
                        │
                        │contains
                        ▼
                ┌───────────────┐
                │  Component    │
                │   (children)  │
                └───────────────┘
```

### Implementation

```cpp
// Component - defines interface for all objects in composition
class MenuComponent {
public:
    virtual ~MenuComponent() = default;

    // Composite methods - for managing children
    virtual void add(std::unique_ptr<MenuComponent> component) {
        throw std::runtime_error("Unsupported operation");
    }

    virtual void remove(MenuComponent* component) {
        throw std::runtime_error("Unsupported operation");
    }

    virtual MenuComponent* getChild(size_t index) {
        throw std::runtime_error("Unsupported operation");
    }

    // Leaf methods - for menu item properties
    virtual std::string getName() const {
        throw std::runtime_error("Unsupported operation");
    }

    virtual std::string getDescription() const {
        throw std::runtime_error("Unsupported operation");
    }

    virtual double getPrice() const {
        throw std::runtime_error("Unsupported operation");
    }

    virtual bool isVegetarian() const {
        throw std::runtime_error("Unsupported operation");
    }

    // Operation method - both leaf and composite implement
    virtual void print() const {
        throw std::runtime_error("Unsupported operation");
    }
};

// Leaf - MenuItem
class MenuItem : public MenuComponent {
private:
    std::string m_name;
    std::string m_description;
    bool m_vegetarian;
    double m_price;

public:
    MenuItem(std::string name, std::string description,
             bool vegetarian, double price)
        : m_name(std::move(name))
        , m_description(std::move(description))
        , m_vegetarian(vegetarian)
        , m_price(price) {}

    std::string getName() const override { return m_name; }
    std::string getDescription() const override { return m_description; }
    bool isVegetarian() const override { return m_vegetarian; }
    double getPrice() const override { return m_price; }

    void print() const override {
        std::cout << "  " << m_name;
        if (m_vegetarian) {
            std::cout << "(v)";
        }
        std::cout << ", $" << m_price << "\n";
        std::cout << "     -- " << m_description << "\n";
    }

    // Note: add(), remove(), getChild() inherited - throw exceptions
};

// Composite - Menu
class Menu : public MenuComponent {
private:
    std::vector<std::unique_ptr<MenuComponent>> m_menuComponents;
    std::string m_name;
    std::string m_description;

public:
    Menu(std::string name, std::string description)
        : m_name(std::move(name))
        , m_description(std::move(description)) {}

    // Composite operations - implemented
    void add(std::unique_ptr<MenuComponent> component) override {
        m_menuComponents.push_back(std::move(component));
    }

    void remove(MenuComponent* component) override {
        auto it = std::find_if(m_menuComponents.begin(), m_menuComponents.end(),
                               [component](const auto& ptr) {
                                   return ptr.get() == component;
                               });
        if (it != m_menuComponents.end()) {
            m_menuComponents.erase(it);
        }
    }

    MenuComponent* getChild(size_t index) override {
        if (index < m_menuComponents.size()) {
            return m_menuComponents[index].get();
        }
        return nullptr;
    }

    std::string getName() const override { return m_name; }
    std::string getDescription() const override { return m_description; }

    // Recursive operation - calls print on all children
    void print() const override {
        std::cout << "\n" << m_name;
        std::cout << ", " << m_description << "\n";
        std::cout << "---------------------\n";

        // Recursively print all children (MenuItems AND Menus)
        for (const auto& component : m_menuComponents) {
            component->print();  // Polymorphic call - works for both!
        }
    }

    // Note: getPrice(), isVegetarian() not overridden - throw exceptions
};

// Client - treats leaf and composite uniformly
class Waitress {
private:
    MenuComponent* m_allMenus;

public:
    explicit Waitress(MenuComponent* allMenus) : m_allMenus(allMenus) {}

    void printMenu() const {
        // Just call print - recursion handles everything!
        m_allMenus->print();
    }
};

// Usage
int main() {
    // Create root menu
    auto allMenus = std::make_unique<Menu>("ALL MENUS", "All menus combined");

    // Create pancake menu
    auto pancakeMenu = std::make_unique<Menu>("PANCAKE HOUSE MENU", "Breakfast");
    pancakeMenu->add(std::make_unique<MenuItem>(
        "Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99));
    pancakeMenu->add(std::make_unique<MenuItem>(
        "Blueberry Pancakes", "Pancakes with fresh blueberries", true, 3.49));

    // Create diner menu
    auto dinerMenu = std::make_unique<Menu>("DINER MENU", "Lunch");
    dinerMenu->add(std::make_unique<MenuItem>(
        "Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato", true, 2.99));
    dinerMenu->add(std::make_unique<MenuItem>(
        "BLT", "Bacon with lettuce & tomato", false, 2.99));

    // Create dessert menu (nested within diner menu!)
    auto dessertMenu = std::make_unique<Menu>("DESSERT MENU", "Dessert of course!");
    dessertMenu->add(std::make_unique<MenuItem>(
        "Apple Pie", "Apple pie with vanilla ice cream", true, 1.59));
    dessertMenu->add(std::make_unique<MenuItem>(
        "Cheesecake", "Creamy New York cheesecake", true, 1.99));

    // Nest dessert menu in diner menu
    dinerMenu->add(std::move(dessertMenu));

    // Build tree
    allMenus->add(std::move(pancakeMenu));
    allMenus->add(std::move(dinerMenu));

    // Client uses uniform interface
    Waitress waitress(allMenus.get());
    waitress.printMenu();  // Prints entire hierarchy recursively!

    return 0;
}
```

### Key Architectural Decisions

1. **Component Base Class**
   - Defines interface for both leaf and composite
   - Provides default implementations (throw exceptions)
   - Allows uniform treatment

2. **Transparency Over Safety**
   - All components have same interface
   - Unsupported operations throw exceptions at runtime
   - Trade-off: Simplicity vs compile-time safety

3. **Recursive Composition**
   - Composites contain components (leaf or composite)
   - Operations delegate to children recursively
   - Arbitrary tree depth supported

4. **Polymorphic Operations**
   - `print()` works uniformly on entire tree
   - No type checking needed
   - Client code simple and elegant

---

## Real-World Example: Embedded Device Hierarchy (Solved)

### Composite Pattern Applied to Embedded Systems

Now let's solve the device hierarchy problem:

```cpp
// Component - base class for all devices and subsystems
class DeviceComponent {
protected:
    std::string m_name;
    DeviceState m_state{DeviceState::UNINITIALIZED};

public:
    explicit DeviceComponent(std::string name) : m_name(std::move(name)) {}
    virtual ~DeviceComponent() = default;

    // Composite operations
    virtual void add(std::unique_ptr<DeviceComponent> component) {
        throw std::runtime_error("Cannot add to leaf device");
    }

    virtual void remove(DeviceComponent* component) {
        throw std::runtime_error("Cannot remove from leaf device");
    }

    virtual DeviceComponent* getChild(size_t index) {
        throw std::runtime_error("Leaf device has no children");
    }

    // Common operations - both leaf and composite implement
    virtual void initialize() = 0;
    virtual void shutdown() = 0;
    virtual void reset() = 0;

    virtual DeviceState getState() const { return m_state; }
    virtual std::string getName() const { return m_name; }

    virtual void printStatus(int indent = 0) const = 0;
    virtual size_t getDeviceCount() const = 0;

    // Power management
    virtual double getCurrentDraw() const = 0;
};

// Leaf - Individual device
class Device : public DeviceComponent {
private:
    uint32_t m_baseAddress;
    double m_currentDrawMa;
    std::function<void()> m_initCallback;
    std::function<void()> m_shutdownCallback;

public:
    Device(std::string name, uint32_t baseAddress, double currentDrawMa)
        : DeviceComponent(std::move(name))
        , m_baseAddress(baseAddress)
        , m_currentDrawMa(currentDrawMa) {}

    void initialize() override {
        if (m_state == DeviceState::RUNNING) {
            return;  // Already initialized
        }

        // Device-specific initialization
        if (m_initCallback) {
            m_initCallback();
        }

        m_state = DeviceState::RUNNING;
        std::cout << "Initialized device: " << m_name << "\n";
    }

    void shutdown() override {
        if (m_state == DeviceState::SHUTDOWN) {
            return;  // Already shutdown
        }

        // Device-specific shutdown
        if (m_shutdownCallback) {
            m_shutdownCallback();
        }

        m_state = DeviceState::SHUTDOWN;
        std::cout << "Shutdown device: " << m_name << "\n";
    }

    void reset() override {
        shutdown();
        // Delay...
        initialize();
    }

    void printStatus(int indent = 0) const override {
        std::string indentation(indent * 2, ' ');
        std::cout << indentation << "Device: " << m_name
                  << " [" << stateToString(m_state) << "] "
                  << "@ 0x" << std::hex << m_baseAddress << std::dec
                  << " (" << m_currentDrawMa << "mA)\n";
    }

    size_t getDeviceCount() const override {
        return 1;
    }

    double getCurrentDraw() const override {
        return (m_state == DeviceState::RUNNING) ? m_currentDrawMa : 0.0;
    }

    void setInitCallback(std::function<void()> callback) {
        m_initCallback = std::move(callback);
    }

    void setShutdownCallback(std::function<void()> callback) {
        m_shutdownCallback = std::move(callback);
    }
};

// Composite - Subsystem (contains devices and/or other subsystems)
class Subsystem : public DeviceComponent {
private:
    std::vector<std::unique_ptr<DeviceComponent>> m_components;

public:
    explicit Subsystem(std::string name) : DeviceComponent(std::move(name)) {}

    // Composite operations - implemented
    void add(std::unique_ptr<DeviceComponent> component) override {
        m_components.push_back(std::move(component));
    }

    void remove(DeviceComponent* component) override {
        auto it = std::find_if(m_components.begin(), m_components.end(),
                               [component](const auto& ptr) {
                                   return ptr.get() == component;
                               });
        if (it != m_components.end()) {
            m_components.erase(it);
        }
    }

    DeviceComponent* getChild(size_t index) override {
        if (index < m_components.size()) {
            return m_components[index].get();
        }
        return nullptr;
    }

    // Recursive operations - delegate to children
    void initialize() override {
        std::cout << "Initializing subsystem: " << m_name << "\n";

        for (auto& component : m_components) {
            component->initialize();  // Recursive!
        }

        m_state = DeviceState::RUNNING;
    }

    void shutdown() override {
        std::cout << "Shutting down subsystem: " << m_name << "\n";

        // Shutdown in reverse order
        for (auto it = m_components.rbegin(); it != m_components.rend(); ++it) {
            (*it)->shutdown();  // Recursive!
        }

        m_state = DeviceState::SHUTDOWN;
    }

    void reset() override {
        shutdown();
        initialize();
    }

    void printStatus(int indent = 0) const override {
        std::string indentation(indent * 2, ' ');
        std::cout << indentation << "Subsystem: " << m_name
                  << " [" << stateToString(m_state) << "]\n";

        // Recursively print children with increased indentation
        for (const auto& component : m_components) {
            component->printStatus(indent + 1);  // Recursive!
        }
    }

    size_t getDeviceCount() const override {
        size_t count = 0;
        for (const auto& component : m_components) {
            count += component->getDeviceCount();  // Recursive!
        }
        return count;
    }

    double getCurrentDraw() const override {
        double total = 0.0;
        for (const auto& component : m_components) {
            total += component->getCurrentDraw();  // Recursive!
        }
        return total;
    }
};

// System controller - uniform treatment of entire hierarchy
class SystemController {
private:
    std::unique_ptr<DeviceComponent> m_rootSystem;

public:
    explicit SystemController(std::unique_ptr<DeviceComponent> rootSystem)
        : m_rootSystem(std::move(rootSystem)) {}

    // Initialize entire system - one call!
    void initializeSystem() {
        std::cout << "\n=== System Initialization ===\n";
        m_rootSystem->initialize();  // Recursively initializes everything!
        std::cout << "System initialized successfully\n";
    }

    // Shutdown entire system - one call!
    void shutdownSystem() {
        std::cout << "\n=== System Shutdown ===\n";
        m_rootSystem->shutdown();  // Recursively shuts down everything!
        std::cout << "System shutdown complete\n";
    }

    // Print entire system status - one call!
    void printSystemStatus() const {
        std::cout << "\n=== System Status ===\n";
        m_rootSystem->printStatus();  // Recursively prints everything!

        std::cout << "\nTotal devices: " << m_rootSystem->getDeviceCount() << "\n";
        std::cout << "Total current draw: " << m_rootSystem->getCurrentDraw()
                  << " mA\n";
    }

    // Reset specific subsystem
    void resetSubsystem(const std::string& subsystemName) {
        // Would need to implement search logic...
        // Demonstrates treating leaf and composite uniformly
    }
};

// Usage - Building the device hierarchy
int main() {
    // Create root system
    auto system = std::make_unique<Subsystem>("Industrial Control System");

    // Create power subsystem
    auto powerSubsystem = std::make_unique<Subsystem>("Power Subsystem");
    powerSubsystem->add(std::make_unique<Device>("Main Power Supply", 0x4000, 5000.0));
    powerSubsystem->add(std::make_unique<Device>("Battery Backup", 0x4100, 500.0));

    // Create voltage regulator subsystem (nested!)
    auto regulatorSubsystem = std::make_unique<Subsystem>("Voltage Regulators");
    regulatorSubsystem->add(std::make_unique<Device>("5V Regulator", 0x4200, 100.0));
    regulatorSubsystem->add(std::make_unique<Device>("3.3V Regulator", 0x4210, 50.0));
    regulatorSubsystem->add(std::make_unique<Device>("1.8V Regulator", 0x4220, 25.0));

    // Nest regulator subsystem in power subsystem
    powerSubsystem->add(std::move(regulatorSubsystem));

    // Create sensor subsystem
    auto sensorSubsystem = std::make_unique<Subsystem>("Sensor Subsystem");
    sensorSubsystem->add(std::make_unique<Device>("Temperature Sensor", 0x5000, 10.0));
    sensorSubsystem->add(std::make_unique<Device>("Pressure Sensor", 0x5100, 15.0));

    // Create environmental sensor subsystem (nested!)
    auto envSensorSubsystem = std::make_unique<Subsystem>("Environmental Sensors");
    envSensorSubsystem->add(std::make_unique<Device>("Humidity Sensor", 0x5200, 8.0));
    envSensorSubsystem->add(std::make_unique<Device>("Air Quality Sensor", 0x5210, 12.0));

    // Nest environmental subsystem in sensor subsystem
    sensorSubsystem->add(std::move(envSensorSubsystem));

    // Create communication subsystem
    auto commSubsystem = std::make_unique<Subsystem>("Communication Subsystem");
    commSubsystem->add(std::make_unique<Device>("Ethernet Controller", 0x6000, 200.0));
    commSubsystem->add(std::make_unique<Device>("WiFi Module", 0x6100, 300.0));

    // Create serial interface subsystem (nested!)
    auto serialSubsystem = std::make_unique<Subsystem>("Serial Interfaces");
    serialSubsystem->add(std::make_unique<Device>("UART", 0x6200, 5.0));
    serialSubsystem->add(std::make_unique<Device>("SPI", 0x6210, 3.0));
    serialSubsystem->add(std::make_unique<Device>("I2C", 0x6220, 2.0));

    // Nest serial subsystem in communication subsystem
    commSubsystem->add(std::move(serialSubsystem));

    // Build complete system hierarchy
    system->add(std::move(powerSubsystem));
    system->add(std::move(sensorSubsystem));
    system->add(std::move(commSubsystem));

    // Create system controller
    SystemController controller(std::move(system));

    // Uniform operations on entire hierarchy!
    controller.initializeSystem();    // Initializes everything recursively
    controller.printSystemStatus();   // Prints entire tree
    controller.shutdownSystem();      // Shuts down everything recursively

    return 0;
}
```

### Benefits in Embedded Context

1. **Hardware Structure Match**
   - Code mirrors hardware organization
   - Boards → Modules → Chips → Peripherals
   - Natural mental model

2. **Uniform Power Management**
   - Power down entire subsystem: `subsystem->shutdown()`
   - Power up in correct order: `subsystem->initialize()`
   - Recursive power state management

3. **Hierarchical Status Reporting**
   - System health view at any level
   - Drill down to specific subsystem
   - Aggregate status automatically

4. **Simplified Initialization**
   - Initialize entire system: one call
   - Proper dependency ordering within subsystems
   - Extensible without client changes

5. **Power Budget Calculation**
   - Calculate subsystem power: `getCurrentDraw()`
   - Recursive aggregation
   - Real-time power monitoring

---

## Composite Benefits and Trade-offs

### Benefits

1. **Uniform Treatment**
   - Leaf and composite treated identically
   - Client code simplified
   - Polymorphic operations

2. **Hierarchical Structures**
   - Arbitrary tree depth
   - Part-whole hierarchies natural
   - Matches real-world organization

3. **Open/Closed Principle**
   - Add new component types easily
   - No client code changes needed
   - Extension without modification

4. **Recursive Operations**
   - Operations automatically traverse tree
   - No explicit traversal code in client
   - Clean, elegant implementation

5. **Flexibility**
   - Move components between composites
   - Restructure tree dynamically
   - Build complex structures from simple parts

### Trade-offs

1. **Overly General Design**
   - Component interface supports all operations
   - Some operations don't make sense for some components
   - Runtime errors instead of compile-time safety

2. **Runtime Exceptions**
   - Calling `add()` on leaf throws exception
   - No compile-time protection
   - Need runtime error handling

3. **Type Safety Sacrificed**
   - Cannot restrict types in composite (e.g., only MenuItems)
   - Can mix incompatible components
   - Type checking deferred to runtime

4. **Performance Overhead**
   - Recursive calls have overhead
   - Virtual function calls throughout tree
   - May be slower than direct access

5. **Complexity for Simple Cases**
   - Overkill if hierarchy is flat
   - Extra classes and indirection
   - Simpler approaches may suffice

---

## Patterns Working Together

### Iterator + Composite: A Powerful Combination

The Iterator and Composite Patterns work beautifully together:

```cpp
// Composite with Iterator support
class MenuComponent {
public:
    virtual std::unique_ptr<Iterator> createIterator() {
        throw std::runtime_error("Unsupported operation");
    }
};

class MenuItem : public MenuComponent {
public:
    // Null Iterator - nothing to iterate for leaf
    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<NullIterator>();
    }
};

class Menu : public MenuComponent {
private:
    std::vector<std::unique_ptr<MenuComponent>> m_components;

public:
    // Composite Iterator - traverses tree structure
    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<CompositeIterator>(m_components);
    }
};

// Composite Iterator - traverses entire tree
class CompositeIterator : public Iterator {
private:
    std::stack<std::unique_ptr<Iterator>> m_stack;

public:
    explicit CompositeIterator(const std::vector<std::unique_ptr<MenuComponent>>& components) {
        // Convert to iterator and push on stack
        // Implementation details...
    }

    bool hasNext() const override {
        if (m_stack.empty()) {
            return false;
        }

        Iterator* iterator = m_stack.top().get();
        if (!iterator->hasNext()) {
            m_stack.pop();
            return hasNext();  // Recursive check next level
        }

        return true;
    }

    MenuItem* next() override {
        if (hasNext()) {
            Iterator* iterator = m_stack.top().get();
            MenuComponent* component = iterator->next();

            // If it's a composite, push its iterator
            if (dynamic_cast<Menu*>(component)) {
                m_stack.push(component->createIterator());
            }

            return dynamic_cast<MenuItem*>(component);
        }
        return nullptr;
    }
};

// Client uses both patterns together
class Waitress {
public:
    void printVegetarianMenu(MenuComponent* allMenus) {
        // Use Iterator to traverse Composite structure!
        auto iterator = allMenus->createIterator();

        while (iterator->hasNext()) {
            MenuItem* item = iterator->next();
            if (item != nullptr && item->isVegetarian()) {
                item->print();
            }
        }
    }
};
```

### Synergy

1. **Iterator Hides Composite Traversal**
   - Complex tree traversal hidden behind simple interface
   - Client doesn't need to know about tree structure
   - Stack-based traversal encapsulated

2. **Composite Provides Structure, Iterator Provides Access**
   - Composite: "How objects are organized"
   - Iterator: "How to access them sequentially"
   - Separation of concerns

3. **Both Promote Uniform Treatment**
   - Composite: Uniform treatment of leaf and composite
   - Iterator: Uniform access to different collections
   - Consistent abstraction

---

## C++ Specific Considerations

### 1. STL Iterators vs Custom Iterators

C++ STL already provides powerful iterator support:

```cpp
// STL iterators
std::vector<MenuItem> items;
for (auto it = items.begin(); it != items.end(); ++it) {
    it->print();
}

// Range-based for (uses iterators internally)
for (const auto& item : items) {
    item.print();
}
```

**When to use Custom Iterators:**
- Abstracting different collection types with uniform interface
- Custom traversal logic (filtered, prioritized, etc.)
- Hiding internal collection implementation
- Working with legacy code or third-party collections

**When to use STL:**
- Standard containers (vector, list, map, etc.)
- Need STL algorithm support
- Performance critical (zero-cost abstraction)
- Want range-based for loop support

### 2. Smart Pointers in Composite

Modern C++ uses smart pointers for ownership:

```cpp
class Menu : public MenuComponent {
private:
    // std::unique_ptr expresses ownership
    std::vector<std::unique_ptr<MenuComponent>> m_components;

public:
    void add(std::unique_ptr<MenuComponent> component) {
        m_components.push_back(std::move(component));  // Transfer ownership
    }

    MenuComponent* getChild(size_t index) {
        // Return raw pointer - no ownership transfer
        return m_components[index].get();
    }
};

// Usage
auto menu = std::make_unique<Menu>("Dinner Menu", "Evening meals");
menu->add(std::make_unique<MenuItem>("Steak", "Grilled ribeye", false, 15.99));
// Ownership transferred to menu
```

**Ownership Semantics:**
- `unique_ptr` in add(): Component belongs to composite
- Raw pointer from getChild(): Borrow, don't own
- Clear ownership model prevents memory leaks

### 3. CRTP for Zero-Cost Iterators

Curiously Recurring Template Pattern (CRTP) can eliminate virtual call overhead:

```cpp
// CRTP Iterator
template<typename Derived>
class IteratorBase {
public:
    bool hasNext() const {
        return static_cast<const Derived*>(this)->hasNextImpl();
    }

    MenuItem* next() {
        return static_cast<Derived*>(this)->nextImpl();
    }
};

class DinerMenuIterator : public IteratorBase<DinerMenuIterator> {
public:
    bool hasNextImpl() const { /* implementation */ }
    MenuItem* nextImpl() { /* implementation */ }
};

// No virtual calls - resolved at compile time!
```

**Trade-off:** Type safety and zero-cost vs flexibility

### 4. Concepts (C++20)

C++20 concepts provide compile-time interface checking:

```cpp
template<typename T>
concept MenuIterator = requires(T iter) {
    { iter.hasNext() } -> std::convertible_to<bool>;
    { iter.next() } -> std::convertible_to<MenuItem*>;
};

template<MenuIterator Iter>
void printMenu(Iter& iterator) {
    while (iterator.hasNext()) {
        MenuItem* item = iterator.next();
        item->print();
    }
}
```

**Benefits:**
- Compile-time checking
- Better error messages
- Documentation in code

### 5. Exception Safety

Composite operations should be exception-safe:

```cpp
void Menu::add(std::unique_ptr<MenuComponent> component) {
    // If push_back throws, unique_ptr automatically cleans up
    m_components.push_back(std::move(component));
}

void Menu::initialize() {
    // Problem: If initialization fails partway through, some devices are initialized
    for (auto& component : m_components) {
        component->initialize();  // What if this throws?
    }

    // Solution: RAII + exception safety
    size_t initialized = 0;
    try {
        for (auto& component : m_components) {
            component->initialize();
            ++initialized;
        }
    } catch (...) {
        // Rollback: shutdown what we initialized
        for (size_t i = 0; i < initialized; ++i) {
            m_components[i]->shutdown();
        }
        throw;  // Re-throw
    }
}
```

### 6. Move Semantics

Modern C++ uses move semantics for efficiency:

```cpp
// Move components into composite - no copying
menu->add(std::move(pancakeMenu));  // pancakeMenu now nullptr

// Move components between composites
auto component = menu->removeAndReturn(0);  // Returns unique_ptr
anotherMenu->add(std::move(component));
```

---

## Pattern Relationships

### Similar Patterns

**Iterator vs Visitor:**
- Iterator: Sequential access to elements
- Visitor: Apply operation to each element
- Can combine: Use Iterator to traverse, Visitor to process

**Composite vs Decorator:**
- Composite: Part-whole hierarchy, contains children
- Decorator: Add responsibilities, wraps one object
- Both use recursive composition

**Composite vs Flyweight:**
- Composite: Many objects, unique state
- Flyweight: Share objects, reduce memory
- Can combine: Flyweight leaves in Composite

### Complementary Patterns

**Iterator + Composite:**
- Iterator traverses Composite structure
- Composite Iterator uses stack for depth-first traversal
- Powerful combination

**Composite + Command:**
- Commands as components in tree
- MacroCommand is Composite of Commands
- Uniform execution

**Iterator + Factory:**
- Factory creates iterators
- `createIterator()` is Factory Method
- Decouples iterator creation

---

## Conclusion

### Iterator Pattern Summary

**Use Iterator Pattern when:**
- You want to access collection elements without exposing representation
- You need uniform interface for different collection types
- You want to support multiple simultaneous traversals
- Collection implementation might change

**Key Principle:** Separate traversal from collection

### Composite Pattern Summary

**Use Composite Pattern when:**
- You want to represent part-whole hierarchies
- You want clients to treat individual objects and compositions uniformly
- Your structure is recursive (trees)
- You need to perform operations on entire hierarchies

**Key Principle:** Treat leaves and composites uniformly

### Combined Power

Together, these patterns enable:
- Flexible collection management (Iterator)
- Hierarchical structures (Composite)
- Uniform traversal of complex trees (Both)

In embedded systems:
- Iterator: Abstract sensor/device collections
- Composite: Model hardware hierarchies
- Together: Powerful device management framework

### Architectural Insight

Both patterns embody the Single Responsibility Principle:
- Iterator: Separate traversal from collection
- Composite: Separate hierarchy structure from operations

Both promote programming to interfaces:
- Iterator: Client uses Iterator interface
- Composite: Client uses Component interface

These patterns are fundamental to building flexible, maintainable systems that can evolve with changing requirements. In embedded systems, they provide the abstraction layers needed to handle hardware complexity while keeping code simple and testable.
