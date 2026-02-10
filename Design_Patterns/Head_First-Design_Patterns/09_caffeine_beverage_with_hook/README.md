# Template Method Pattern - Caffeine Beverage with Hook

## Overview

This project demonstrates the **Template Method Pattern**, a behavioral design pattern that defines the skeleton of an algorithm in a base class method, deferring some steps to subclasses. Subclasses can redefine certain steps of an algorithm without changing the algorithm's structure.

## Pattern Intent

**Template Method Pattern** defines the skeleton of an algorithm in a method, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.

## The Problem

Without the Template Method pattern, you face algorithm duplication:

```cpp
// BAD: Each beverage duplicates the preparation algorithm
class Coffee {
    void prepareRecipe() {
        boilWater();
        brewCoffeeGrinds();
        pourInCup();
        addSugarAndMilk();
    }
    // ... duplicate methods
};

class Tea {
    void prepareRecipe() {
        boilWater();          // DUPLICATE
        steepTeaBag();
        pourInCup();          // DUPLICATE
        addLemon();
    }
    // ... duplicate methods
};
```

**Problems:**
- Algorithm structure duplicated in every class
- Common steps (`boilWater()`, `pourInCup()`) duplicated
- Cannot enforce algorithm consistency
- Changes require modifying all classes
- Risk of algorithm variations and bugs

## The Solution

Template Method pattern extracts the algorithm structure into a base class:

```cpp
// GOOD: Algorithm defined once in base class
class CaffeineBeverage {
public:
    void prepareRecipe() {  // Template method
        boilWater();        // Concrete method
        brew();             // Abstract method
        pourInCup();        // Concrete method
        if (customerWantsCondiments()) {  // Hook
            addCondiments(); // Abstract method
        }
    }

protected:
    virtual void brew() = 0;
    virtual void addCondiments() = 0;
    virtual bool customerWantsCondiments() { return true; }
};

// Subclasses implement only varying steps
class Coffee : public CaffeineBeverage {
    void brew() override { /* coffee brewing */ }
    void addCondiments() override { /* coffee condiments */ }
};
```

## Key Components

### 1. Template Method
- **Non-virtual method** that defines algorithm skeleton
- Controls algorithm structure (cannot be overridden)
- Calls abstract methods, concrete methods, and hooks
- Example: `prepareRecipe()`

### 2. Abstract Methods (Pure Virtual)
- **Must be implemented** by subclasses
- Represent steps that vary between implementations
- Example: `brew()`, `addCondiments()`

### 3. Concrete Methods
- **Default implementations** in base class
- Common to all subclasses
- Can be overridden but usually aren't
- Example: `boilWater()`, `pourInCup()`

### 4. Hooks
- **Virtual methods with default behavior**
- Subclasses can override (optional)
- Enable conditional logic in algorithm
- Example: `customerWantsCondiments()`

## Hollywood Principle

**"Don't call us, we'll call you"**

The Template Method pattern implements the Hollywood Principle through inversion of control:

- **Base class (high-level)** controls algorithm flow
- **Subclasses (low-level)** implement specific steps
- Subclasses never call the template method - it calls them
- Framework calls your code, not vice versa

```cpp
// Base class calls subclass methods
void CaffeineBeverage::prepareRecipe() {
    brew();           // Base calls subclass
    addCondiments();  // Base calls subclass
}

// Subclass just implements, doesn't control
class Coffee : public CaffeineBeverage {
    void brew() override {
        // Just implements this step
        // Doesn't decide when it's called
    }
};
```

## Hook vs Abstract Method

### Abstract Method
```cpp
virtual void brew() = 0;  // Must implement
```
- **Required** - subclass must implement
- No default behavior
- Use when: Step is mandatory and varies

### Hook
```cpp
virtual bool customerWantsCondiments() {
    return true;  // Default behavior
}
```
- **Optional** - subclass can override
- Has default behavior
- Use when: Step is optional or has sensible default

## Benefits

1. **Eliminates Code Duplication**
   - Algorithm defined once in base class
   - Common steps implemented once
   - Subclasses only implement variations

2. **Enforces Algorithm Consistency**
   - Algorithm structure protected from changes
   - All subclasses follow same sequence
   - Prevents accidental reordering

3. **Easy to Extend**
   - Adding new beverage: implement 2 methods
   - Algorithm already defined in base class
   - No code duplication

4. **Central Control**
   - Change algorithm once, affects all subclasses
   - Bug fixes in one place
   - Consistent behavior across system

5. **Flexibility Through Hooks**
   - Optional extension points
   - Customize behavior without breaking algorithm
   - Default behavior if not overridden

## Trade-offs

1. **Inheritance-Based**
   - Requires subclassing (tight coupling)
   - Less flexible than composition-based patterns
   - Cannot change behavior at runtime

2. **Rigid Structure**
   - All subclasses must follow same algorithm
   - Cannot change step order in subclasses
   - Not suitable for completely different algorithms

3. **More Classes**
   - Each variant needs a subclass
   - Can lead to class proliferation

## When to Use

✅ **Use Template Method when:**
- Multiple classes share same algorithm structure
- Want to enforce algorithm consistency
- Need central control over algorithm
- Have clear invariant (common) and variant (specific) steps
- Algorithm structure should not change

❌ **Don't use when:**
- Algorithms have completely different structures
- Need to change algorithm at runtime (use Strategy instead)
- Prefer composition over inheritance
- Don't have clear common structure

## Real-World Applications

- **Initialization sequences** (robot startup, device initialization)
- **Data processing pipelines** (parse → process → validate → output)
- **Test frameworks** (setUp → test → tearDown)
- **Document generation** (header → content → footer)
- **Game AI** (sense → think → act)
- **Network protocols** (connect → authenticate → transfer → disconnect)

## Project Structure

```
09_caffeine_beverage_with_hook/
├── CMakeLists.txt                    # Build configuration
├── main.cpp                          # Demonstration program
├── inc/                              # Header files
│   ├── CaffeineBeverageWithHook.h   # Abstract base class (template method)
│   ├── CoffeeWithHook.h             # Concrete coffee implementation
│   └── TeaWithHook.h                # Concrete tea implementation
├── src/                              # Source files (empty - header-only)
├── out/build/                        # Build output
├── scripts/                          # Build and run scripts
│   ├── conf.sh                      # Configure CMake
│   ├── build.sh                     # Build project
│   ├── run.sh                       # Run executable
│   └── all.sh                       # Run all steps
├── UML/
│   └── diagram.puml                 # Class diagram
├── Template_Method_Pattern.md              # Detailed pattern analysis
└── README.md                        # This file
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

The program demonstrates beverage preparation with user interaction:

```
Making tea...
----------------------------------------
Boiling water
Steeping the tea
Pouring into cup
Would you like lemon with your tea (y/n)? y
Adding Lemon

Making coffee...
----------------------------------------
Boiling water
Dripping Coffee through filter
Pouring into cup
Would you like milk and sugar with your coffee (y/n)? n
```

## Code Example

### Base Class (Template Method)

```cpp
class CaffeineBeverageWithHook {
public:
    // Template method - defines algorithm skeleton
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments()) {
            addCondiments();
        }
    }

protected:
    // Abstract methods - subclasses must implement
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    // Concrete methods - default implementations
    void boilWater() { std::cout << "Boiling water\n"; }
    void pourInCup() { std::cout << "Pouring into cup\n"; }

    // Hook - optional override
    virtual bool customerWantsCondiments() { return true; }
};
```

### Concrete Subclass

```cpp
class CoffeeWithHook : public CaffeineBeverageWithHook {
protected:
    void brew() override {
        std::cout << "Dripping Coffee through filter\n";
    }

    void addCondiments() override {
        std::cout << "Adding Sugar and Milk\n";
    }

    bool customerWantsCondiments() override {
        std::string answer = getUserInput();
        return !answer.empty() && tolower(answer[0]) == 'y';
    }
};
```

## Design Principles Applied

1. **Hollywood Principle**
   - "Don't call us, we'll call you"
   - Base class controls flow, subclasses implement steps
   - Inversion of control

2. **DRY (Don't Repeat Yourself)**
   - Algorithm defined once in base class
   - No code duplication

3. **Open/Closed Principle**
   - Base class closed for modification (algorithm fixed)
   - System open for extension (new subclasses)

4. **Single Responsibility Principle**
   - Base class: algorithm structure
   - Subclasses: specific implementations

## C++ Specific Features

- **Non-Virtual Interface (NVI) idiom**: Template method is non-virtual
- **Pure virtual functions**: Abstract methods subclasses must implement
- **Virtual destructor**: Safe polymorphic deletion
- **Protected interface**: Subclass customization points
- **Smart pointers**: Modern C++ memory management
- **const correctness**: Proper const methods

## Related Patterns

- **Strategy Pattern**: Similar intent but uses composition instead of inheritance, allows runtime behavior change
- **Factory Method**: Often used as a step in template method
- **Hook Method**: Extension of template method providing optional customization points

## Further Reading

- Design Patterns: Elements of Reusable Object-Oriented Software (Gang of Four)
- Head First Design Patterns (Freeman & Freeman)
- Template_Method_Pattern.md (detailed analysis with real-world examples)

## Author Notes

This implementation demonstrates modern C++20 features and follows SonarQube code quality standards. The pattern is implemented using the Non-Virtual Interface (NVI) idiom, which provides stronger encapsulation and control over algorithm invariants compared to the Java implementation.

The Robotics real-world example in Template_Method_Pattern.md shows how Template Method pattern is crucial for safety-critical systems where algorithm consistency must be enforced across different hardware platforms.
