# Abstract Factory Pattern - Sensor Platform Families

## Overview

This project demonstrates the **Abstract Factory Pattern**, a creational design pattern that provides an interface for creating families of related or dependent objects without specifying their concrete classes.

## Pattern Intent

**Abstract Factory Pattern** provides an interface for creating families of related or dependent objects without specifying their concrete classes.

## The Problem

Without the Abstract Factory pattern, you risk mixing incompatible objects:

```cpp
// BAD: Mixing sensors from different platforms

class WeatherStation {
public:
    WeatherStation() {
        // PROBLEM: Mixing ARM and ESP32 sensors!
        tempSensor = new ARMTemperatureSensor();    // ARM platform
        pressureSensor = new ESP32PressureSensor(); // ESP32 platform (INCOMPATIBLE!)

        // These sensors use different communication protocols:
        // - ARM uses I2C peripheral registers
        // - ESP32 uses different I2C driver API
        // Result: One sensor works, other fails!
    }
};
```

**Problems:**
- **Platform mismatch**: Sensors from different platforms mixed together
- **Communication conflicts**: Different I2C/SPI APIs don't work together
- **Hard to switch platforms**: Must change sensor creation in many places
- **No consistency guarantee**: Can accidentally mix incompatible sensors
- **Tight coupling**: Client knows about all concrete sensor classes

## The Solution

Abstract Factory ensures family consistency:

```cpp
// GOOD: Factory ensures all sensors from same platform

class SensorFactory {
public:
    virtual unique_ptr<TemperatureSensor> createTemperatureSensor() = 0;
    virtual unique_ptr<PressureSensor> createPressureSensor() = 0;
};

class ARMSensorFactory : public SensorFactory {
    // Creates ONLY ARM sensors (guaranteed consistency)
    unique_ptr<TemperatureSensor> createTemperatureSensor() override {
        return make_unique<ARMTemperatureSensor>();
    }
    unique_ptr<PressureSensor> createPressureSensor() override {
        return make_unique<ARMPressureSensor>();
    }
};

class WeatherStation {
    WeatherStation(const SensorFactory& factory) {
        // All sensors from SAME platform (consistent!)
        tempSensor = factory.createTemperatureSensor();
        pressureSensor = factory.createPressureSensor();
    }
};

// Usage: All sensors guaranteed to be ARM sensors
ARMSensorFactory armFactory;
WeatherStation station(armFactory);
```

## Key Components

### 1. Abstract Factory (Interface)
- **SensorFactory**: Declares creation methods for product family
- Returns abstract product types (interfaces)

### 2. Concrete Factories
- **ARMSensorFactory**: Creates ARM platform sensors
- **ESP32SensorFactory**: Creates ESP32 platform sensors
- Each factory creates complete family of compatible products

### 3. Abstract Products (Interfaces)
- **TemperatureSensor**: Interface for temperature sensors
- **PressureSensor**: Interface for pressure sensors
- Define common operations

### 4. Concrete Products
- **ARMTemperatureSensor**: ARM-specific implementation
- **ARMPressureSensor**: ARM-specific implementation
- **ESP32TemperatureSensor**: ESP32-specific implementation
- **ESP32PressureSensor**: ESP32-specific implementation

### 5. Client
- **WeatherStation**: Uses abstract interfaces only
- Doesn't know about concrete products
- Platform-independent

## Pattern Structure

```
Abstract Factory          Abstract Product
┌─────────────┐          ┌──────────────┐
│SensorFactory│          │Temperature   │
│             │          │Sensor        │
│create...()  │          └──────────────┘
└─────────────┘                 △
       △                        │
       │                        │
    ┌──┴──┐                  ┌──┴──┐
    │     │                  │     │
┌───┴─┐ ┌─┴───┐          ┌───┴──┐ ┌┴────┐
│ARM  │ │ESP32│          │ARM   │ │ESP32│
│     │ │     │          │Temp  │ │Temp │
└─────┘ └─────┘          └──────┘ └─────┘

Creates families of related products
```

## Benefits

1. **Family Consistency**
   - All products from same factory are compatible
   - Cannot mix ARM sensors with ESP32 sensors
   - Compile-time enforcement

2. **Platform Independence**
   - Client code works with any platform
   - Switch platform by changing factory
   - No client code changes needed

3. **Easy to Extend**
   - Add new platform: Create new factory
   - Add new product type: Add to all factories
   - Existing code unchanged

4. **Dependency Inversion**
   - Client depends on abstractions (interfaces)
   - Not on concrete implementations
   - Follows SOLID principles

5. **Single Point of Control**
   - Factory controls which products are created
   - Consistent product families guaranteed
   - Easy to enforce compatibility rules

## Trade-offs

1. **Many Classes**
   - Factory hierarchy + Product hierarchies
   - More classes to maintain

2. **Hard to Add New Product Types**
   - Must modify all factories
   - More changes when product family grows

3. **More Complex**
   - Compared to simple Factory Method
   - Requires understanding of multiple hierarchies

## When to Use

✅ **Use Abstract Factory when:**
- System must work with multiple product families
- Products in a family must be used together
- Need to ensure product compatibility
- Want to hide concrete product classes
- Platform/configuration determines product family

❌ **Don't use when:**
- Only one product family exists
- Products don't need to be related
- Simple Factory Method is sufficient
- Product families change frequently

## Real-World Applications

- **GUI Toolkits** (Windows widgets, macOS widgets, Linux widgets)
- **Embedded Platforms** (ARM sensors, ESP32 sensors, STM32 sensors)
- **Database Drivers** (MySQL factory, PostgreSQL factory, SQLite factory)
- **Cross-Platform Libraries** (platform-specific implementations)
- **Game Engines** (DirectX factory, OpenGL factory, Vulkan factory)

## Project Structure

```
02_abstract_factory_pattern/
├── CMakeLists.txt                    # Build configuration
├── main.cpp                          # Demonstration program
├── inc/                              # Header files
│   ├── SensorFactory.h              # Abstract factory interface
│   ├── ARMSensorFactory.h           # ARM concrete factory
│   ├── ESP32SensorFactory.h         # ESP32 concrete factory
│   ├── TemperatureSensor.h          # Abstract product interface
│   ├── PressureSensor.h             # Abstract product interface
│   ├── ARMTemperatureSensor.h       # ARM concrete product
│   ├── ARMPressureSensor.h          # ARM concrete product
│   ├── ESP32TemperatureSensor.h     # ESP32 concrete product
│   ├── ESP32PressureSensor.h        # ESP32 concrete product
│   └── WeatherStation.h             # Client
├── src/                              # Source files (empty - header-only)
├── out/build/                        # Build output
├── scripts/                          # Build and run scripts
│   ├── conf.sh                      # Configure CMake
│   ├── build.sh                     # Build project
│   ├── run.sh                       # Run executable
│   └── all.sh                       # Run all steps
├── UML/
│   └── Abstract_Factory_Pattern.puml # Class diagram
├── Abstract_Factory.md              # Detailed pattern analysis
└── README.md                        # This file
```

## Building and Running

### Quick Start (All-in-One)

```bash
cd scripts
./all.sh
```

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

The program demonstrates three scenarios:

```
=== DEMONSTRATION 1: ARM Platform ===
- Creates ARM sensor factory
- All sensors use ARM peripherals
- Consistent communication (I2C/SPI)

=== DEMONSTRATION 2: ESP32 Platform ===
- Creates ESP32 sensor factory
- All sensors use ESP32 drivers
- Consistent platform-specific implementation

=== DEMONSTRATION 3: Runtime Platform Selection ===
- Selects factory based on detected platform
- Client code unchanged
- Same WeatherStation works with any platform
```

## Code Example

```cpp
#include "ARMSensorFactory.h"
#include "WeatherStation.h"

int main() {
    // Create factory for specific platform
    ARMSensorFactory armFactory;

    // Client uses abstract factory
    WeatherStation station(armFactory);

    // Display readings (platform-independent)
    station.displayReadings();

    return 0;
}
```

## Design Principles Applied

1. **Dependency Inversion Principle**
   - Client depends on abstractions (interfaces)
   - Not on concrete implementations
   - High-level policy independent of low-level details

2. **Open/Closed Principle**
   - Open for extension (new factories, new products)
   - Closed for modification (existing code unchanged)

3. **Single Responsibility Principle**
   - Factory: Creates product families
   - Products: Provide specific functionality
   - Client: Uses products

4. **Interface Segregation Principle**
   - Separate interfaces for each product type
   - Clients depend only on needed interfaces

## Abstract Factory vs Factory Method

| Aspect | Abstract Factory | Factory Method |
|--------|------------------|----------------|
| **Creates** | Family of related products | Single product |
| **Structure** | Multiple factory methods | One factory method |
| **Usage** | Platform/theme selection | Single object creation |
| **Complexity** | Higher (multiple hierarchies) | Lower (single hierarchy) |
| **Flexibility** | Change entire family at once | Change single product |

## C++ Specific Features

- **Smart pointers**: `unique_ptr` for automatic memory management
- **Abstract interfaces**: Pure virtual functions
- **Override keyword**: Clear virtual function overriding
- **Modern initialization**: `make_unique` for safety
- **Const correctness**: Const factory methods
- **Virtual destructor**: Safe polymorphic deletion

## Related Patterns

- **Factory Method**: Often used to implement product creation in Abstract Factory
- **Singleton**: Factories are often implemented as Singletons
- **Prototype**: Alternative for creating product families
- **Builder**: Can use Abstract Factory for components

## Further Reading

- Design Patterns: Elements of Reusable Object-Oriented Software (Gang of Four)
- Head First Design Patterns (Freeman & Freeman)
- Abstract_Factory.md (detailed analysis with embedded systems examples)

## Author Notes

This implementation demonstrates Abstract Factory with embedded sensor platforms, showing how the pattern ensures platform-specific sensors work together correctly. The pattern prevents mixing incompatible sensors (ARM with ESP32), which would cause runtime failures in real embedded systems.

The embedded example highlights why Abstract Factory is crucial in cross-platform development: it guarantees that all components come from the same platform, ensuring they communicate correctly through compatible APIs and protocols.
