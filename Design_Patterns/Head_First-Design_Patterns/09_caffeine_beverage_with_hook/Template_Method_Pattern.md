# Template Method Pattern - Comprehensive Analysis

## Pattern Overview

**Template Method Pattern** defines the skeleton of an algorithm in a method, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.

**Key Intent:** Define the structure of an algorithm once, and let subclasses provide specific implementations for certain steps.

**Also Known As:** Algorithmic Skeleton Pattern

**Core Concept:** The template method contains the algorithm structure. It calls abstract methods that subclasses must implement, concrete methods that provide default behavior, and hooks that subclasses can optionally override.

---

## The Problem: Duplicated Algorithms

### Bad Architecture Example: Copy-Pasted Algorithm Variations

```cpp
// BAD: Coffee and Tea classes duplicate the preparation algorithm
class Coffee {
public:
    void prepareRecipe() {
        boilWater();
        brewCoffeeGrinds();
        pourInCup();
        addSugarAndMilk();
    }

    void boilWater() {
        std::cout << "Boiling water\n";
    }

    void brewCoffeeGrinds() {
        std::cout << "Dripping Coffee through filter\n";
    }

    void pourInCup() {
        std::cout << "Pouring into cup\n";
    }

    void addSugarAndMilk() {
        std::cout << "Adding Sugar and Milk\n";
    }
};

class Tea {
public:
    void prepareRecipe() {
        boilWater();
        steepTeaBag();
        pourInCup();
        addLemon();
    }

    void boilWater() {
        std::cout << "Boiling water\n";
    }

    void steepTeaBag() {
        std::cout << "Steeping the tea\n";
    }

    void pourInCup() {
        std::cout << "Pouring into cup\n";
    }

    void addLemon() {
        std::cout << "Adding Lemon\n";
    }
};

// PROBLEMS:
// 1. Algorithm structure duplicated: boilWater → brew → pourInCup → addCondiments
// 2. Common steps duplicated: boilWater(), pourInCup()
// 3. Cannot enforce algorithm consistency
// 4. Changes to algorithm require modifying ALL classes
// 5. No guarantee classes follow same sequence
```

### Pain Points

1. **Algorithm Duplication**
   - Same algorithm structure copied across multiple classes
   - `prepareRecipe()` duplicated in Coffee and Tea
   - Algorithm steps in same order but scattered across classes
   - Cannot change algorithm without updating all copies

2. **Code Duplication**
   - `boilWater()` implemented identically in both classes
   - `pourInCup()` implemented identically in both classes
   - Duplicated code = duplicated bugs
   - Bug fixes must be applied everywhere

3. **No Enforcement of Algorithm Structure**
   - Nothing prevents subclass from changing algorithm order
   - Could accidentally do: brew → pourInCup → boilWater (wrong order!)
   - No guarantee all beverages follow same preparation sequence
   - Algorithm consistency not enforced

4. **Violates DRY Principle (Don't Repeat Yourself)**
   - Common algorithm logic repeated
   - Common implementation repeated
   - Maintenance nightmare

5. **Difficult to Add New Beverages**
   ```cpp
   // Adding hot chocolate requires duplicating entire algorithm again
   class HotChocolate {
   public:
       void prepareRecipe() {
           boilWater();           // Duplicate #3
           addChocolate();
           pourInCup();           // Duplicate #3
           addWhippedCream();
       }

       void boilWater() {         // Duplicate #3 of same code
           std::cout << "Boiling water\n";
       }

       void pourInCup() {         // Duplicate #3 of same code
           std::cout << "Pouring into cup\n";
       }

       // ... more duplicated code
   };
   ```

6. **Cannot Change Algorithm Centrally**
   - Want to add "preheat cup" step before pouring?
   - Must modify Coffee, Tea, HotChocolate, and every other beverage
   - 10 beverage classes = 10 places to change
   - Easy to miss one, creating inconsistent behavior

### Example of Cascading Problems

```cpp
// As beverage menu grows, duplication explodes
class Coffee {
    void prepareRecipe() { /* 4 steps */ }
    void boilWater() { /* duplicate 1 */ }
    void pourInCup() { /* duplicate 1 */ }
};

class Tea {
    void prepareRecipe() { /* 4 steps - duplicate algorithm */ }
    void boilWater() { /* duplicate 2 */ }
    void pourInCup() { /* duplicate 2 */ }
};

class HotChocolate {
    void prepareRecipe() { /* 4 steps - duplicate algorithm */ }
    void boilWater() { /* duplicate 3 */ }
    void pourInCup() { /* duplicate 3 */ }
};

class Espresso {
    void prepareRecipe() { /* 4 steps - duplicate algorithm */ }
    void boilWater() { /* duplicate 4 */ }
    void pourInCup() { /* duplicate 4 */ }
};

// DISASTER:
// 1. Algorithm duplicated 4 times
// 2. boilWater() duplicated 4 times
// 3. pourInCup() duplicated 4 times
// 4. To add "preheat cup" step, must change 4 classes
// 5. Bug in boilWater()? Fix it 4 times
// 6. New beverage? Duplicate everything again (5th time!)
```

**Real Production Bug Example:**

```cpp
// Bug discovered: water temperature should be different for different beverages
class Coffee {
    void boilWater() {
        std::cout << "Boiling water to 96°C\n";  // Fixed for coffee
    }
};

class Tea {
    void boilWater() {
        std::cout << "Boiling water\n";  // ❌ BUG: Not updated! Still at 100°C
    }
};

class HotChocolate {
    void boilWater() {
        std::cout << "Boiling water to 85°C\n";  // Fixed for chocolate
    }
};

class Espresso {
    void boilWater() {
        std::cout << "Boiling water\n";  // ❌ BUG: Not updated!
    }
};

// Result: Inconsistent behavior across beverages
// Developer fixed 2 out of 4 classes, forgot the others
// Tea and Espresso still using wrong temperature
// Takes 2 hours to find bug in production
```

**Result:** System becomes a maintenance nightmare. Algorithm changes require touching multiple classes. Bugs multiply. Adding new beverage types becomes increasingly risky and error-prone.

### UML Diagram: Bad Design

See `UML/Bad_Duplicated_Algorithm.puml` for the class diagram showing Coffee and Tea with duplicated algorithm logic and no shared base class (red-highlighted problem classes).

---

## Design Principles

### 1. Hollywood Principle: "Don't Call Us, We'll Call You"

**Definition:** High-level components should control the flow, calling low-level components. Low-level components shouldn't call high-level components.

**In Template Method:**
- Base class (high-level) defines algorithm and calls methods
- Subclasses (low-level) implement methods but don't control flow
- Subclasses never call the template method - it calls them

**Before Template Method:**

```cpp
// BAD: Low-level component (Coffee) controls its own flow
class Coffee {
public:
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }
    // Coffee class controls when and how steps are called
    // Each subclass duplicates this control logic
};
```

**After Template Method:**

```cpp
// GOOD: High-level component (CaffeineBeverage) controls flow
class CaffeineBeverage {
public:
    void prepareRecipe() {  // Template method (high-level control)
        boilWater();
        brew();              // "We'll call you" - calls subclass method
        pourInCup();
        if (customerWantsCondiments()) {
            addCondiments();  // "We'll call you"
        }
    }
protected:
    virtual void brew() = 0;           // Subclass implements
    virtual void addCondiments() = 0;  // Subclass implements
};

// Coffee doesn't control flow - it's called by base class
class Coffee : public CaffeineBeverage {
protected:
    void brew() override {
        // Just implements this step
        // Doesn't decide when it's called
    }
};
```

**Key Insight:** Inversion of control. The framework (base class) calls you, you don't call the framework.

### 2. Don't Repeat Yourself (DRY Principle)

**Definition:** Every piece of knowledge should have a single, unambiguous representation in the system.

**Template Method enforces DRY:**

```cpp
// BEFORE: Algorithm repeated in every class
class Coffee {
    void prepareRecipe() {
        boilWater();  // Step 1
        brew();       // Step 2
        pourInCup();  // Step 3
        addCondiments();  // Step 4
    }
};

class Tea {
    void prepareRecipe() {
        boilWater();  // DUPLICATE Step 1
        brew();       // DUPLICATE Step 2
        pourInCup();  // DUPLICATE Step 3
        addCondiments();  // DUPLICATE Step 4
    }
};

// AFTER: Algorithm defined once in base class
class CaffeineBeverage {
    void prepareRecipe() {  // SINGLE DEFINITION
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }
};
```

Common code moves to base class, varying parts stay in subclasses.

### 3. Open/Closed Principle

**Definition:** Classes should be open for extension but closed for modification.

**Template Method achieves this:**

```cpp
// Base class CLOSED for modification
class CaffeineBeverage {
public:
    void prepareRecipe() {  // Algorithm fixed, won't change
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }
protected:
    virtual void brew() = 0;
    virtual void addCondiments() = 0;
};

// System OPEN for extension - add new beverages without modifying base
class HotChocolate : public CaffeineBeverage {
    void brew() override { /* chocolate-specific */ }
    void addCondiments() override { /* chocolate-specific */ }
};

// Added new beverage WITHOUT changing CaffeineBeverage
// Base class algorithm remains untouched
```

### 4. Liskov Substitution Principle (LSP)

**Definition:** Subclasses should be substitutable for their base class without breaking program correctness.

**Template Method enforces LSP:**

```cpp
void serveBeverage(CaffeineBeverage* beverage) {
    beverage->prepareRecipe();  // Works for ANY subclass
    // Coffee, Tea, HotChocolate all work correctly
    // Algorithm structure guaranteed consistent
}

Coffee coffee;
Tea tea;
serveBeverage(&coffee);  // ✓ Works
serveBeverage(&tea);     // ✓ Works
// Both follow same algorithm structure
```

Because template method enforces algorithm structure, all subclasses behave consistently.

### 5. Single Responsibility Principle

**Separation of responsibilities:**

- **Base class responsibility:** Define and control algorithm structure
- **Subclass responsibility:** Implement specific steps

```cpp
class CaffeineBeverage {
    // Responsible for: Algorithm structure and control flow
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }
};

class Coffee : public CaffeineBeverage {
    // Responsible for: Coffee-specific implementations
    void brew() override { /* coffee brewing */ }
    void addCondiments() override { /* coffee condiments */ }
};

class Tea : public CaffeineBeverage {
    // Responsible for: Tea-specific implementations
    void brew() override { /* tea brewing */ }
    void addCondiments() override { /* tea condiments */ }
};
```

Clear separation: **what** to do (base) vs **how** to do it (subclasses).

---

## The Solution: Template Method Pattern

### Structure

```text
┌──────────────────────────────────────────────────┐
│          AbstractClass                           │
│     (CaffeineBeverage)                           │
├──────────────────────────────────────────────────┤
│ + templateMethod()              [final]          │ ← Template Method
│ # primitiveOperation1()         [abstract]       │ ← Must implement
│ # primitiveOperation2()         [abstract]       │ ← Must implement
│ # concreteOperation()                            │ ← Default implementation
│ # hook()                        [hook]           │ ← Optional override
└───────────────┬──────────────────────────────────┘
                │
        ┌───────┴────────┐
        ↓                ↓
┌──────────────┐  ┌──────────────┐
│ ConcreteA    │  │ ConcreteB    │
│ (Coffee)     │  │ (Tea)        │
├──────────────┤  ├──────────────┤
│ + primitive1 │  │ + primitive1 │
│ + primitive2 │  │ + primitive2 │
│ + hook()     │  └──────────────┘
└──────────────┘

Key Components:
1. Template Method: Defines algorithm skeleton (final, non-overridable)
2. Abstract Methods: Steps subclasses must implement
3. Concrete Methods: Default implementations (can use as-is)
4. Hooks: Optional extension points (empty default, can override)
```

### Key Components

1. **Template Method (Algorithm Skeleton)**
   - Defines the fixed algorithm structure
   - Calls primitive operations in specific order
   - Should be `final` (non-virtual in C++) to prevent overriding
   - Controls the overall algorithm flow

2. **Abstract Primitive Operations**
   - Pure virtual methods (abstract in Java)
   - Subclasses MUST implement
   - Represent steps that vary between subclasses
   - Called by template method

3. **Concrete Operations**
   - Methods with default implementation in base class
   - Common to all subclasses
   - Can be overridden if needed, but usually aren't
   - Reduce code duplication

4. **Hooks**
   - Virtual methods with empty or default implementation
   - Subclasses CAN override (optional)
   - Provide extension points without forcing implementation
   - Enable conditional logic in algorithm

### How It Works

```cpp
// 1. Base class defines algorithm structure
class CaffeineBeverage {
public:
    // Template method: The algorithm skeleton (final - cannot override)
    void prepareRecipe() {
        boilWater();           // Concrete method (shared)
        brew();                // Abstract method (varies)
        pourInCup();           // Concrete method (shared)

        if (customerWantsCondiments()) {  // Hook (optional)
            addCondiments();   // Abstract method (varies)
        }
    }

protected:
    // Concrete methods: Default implementations
    void boilWater() {
        std::cout << "Boiling water\n";
    }

    void pourInCup() {
        std::cout << "Pouring into cup\n";
    }

    // Abstract methods: Subclasses must implement
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    // Hook: Optional override
    virtual bool customerWantsCondiments() {
        return true;  // Default: yes
    }
};

// 2. Subclass implements specific steps
class Coffee : public CaffeineBeverage {
protected:
    void brew() override {
        std::cout << "Dripping Coffee through filter\n";
    }

    void addCondiments() override {
        std::cout << "Adding Sugar and Milk\n";
    }

    // Override hook for custom behavior
    bool customerWantsCondiments() override {
        return getUserInput();  // Ask user
    }
};

// 3. Client uses template method
Coffee coffee;
coffee.prepareRecipe();  // Executes algorithm with Coffee-specific steps

// Output:
// Boiling water
// Dripping Coffee through filter
// Pouring into cup
// Would you like milk and sugar? (y/n): y
// Adding Sugar and Milk
```

**Critical Insight:** The algorithm structure is fixed in the template method. Subclasses cannot change the order of steps—they can only provide implementations for specific steps.

### Complete Example: Caffeine Beverage

```cpp
#include <iostream>
#include <string>

// Abstract base class
class CaffeineBeverage {
public:
    // Template method: Defines algorithm skeleton
    // Final (non-virtual) in C++ - cannot be overridden
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();

        if (customerWantsCondiments()) {
            addCondiments();
        }
    }

protected:
    // Abstract methods: Subclasses must implement
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    // Concrete methods: Default implementations
    void boilWater() {
        std::cout << "Boiling water\n";
    }

    void pourInCup() {
        std::cout << "Pouring into cup\n";
    }

    // Hook: Optional override
    virtual bool customerWantsCondiments() {
        return true;  // Default behavior
    }
};

// Concrete subclass: Coffee
class Coffee : public CaffeineBeverage {
protected:
    void brew() override {
        std::cout << "Dripping Coffee through filter\n";
    }

    void addCondiments() override {
        std::cout << "Adding Sugar and Milk\n";
    }

    bool customerWantsCondiments() override {
        std::cout << "Would you like milk and sugar? (y/n): ";
        std::string answer;
        std::getline(std::cin, answer);
        return !answer.empty() && (answer[0] == 'y' || answer[0] == 'Y');
    }
};

// Concrete subclass: Tea
class Tea : public CaffeineBeverage {
protected:
    void brew() override {
        std::cout << "Steeping the tea\n";
    }

    void addCondiments() override {
        std::cout << "Adding Lemon\n";
    }

    bool customerWantsCondiments() override {
        std::cout << "Would you like lemon? (y/n): ";
        std::string answer;
        std::getline(std::cin, answer);
        return !answer.empty() && (answer[0] == 'y' || answer[0] == 'Y');
    }
};

// Client code
int main() {
    Coffee coffee;
    Tea tea;

    std::cout << "Making coffee...\n";
    coffee.prepareRecipe();

    std::cout << "\nMaking tea...\n";
    tea.prepareRecipe();
}
```

### Real-World Robot Example with Template Method

```cpp
// Robot startup template
class AutonomousRobot {
public:
    // Template method: Startup sequence (non-virtual - cannot override)
    void startup() {
        powerOnSelfTest();
        initializeCommunication();
        calibrateSensors();      // Abstract: hardware-specific
        initializeActuators();   // Abstract: hardware-specific
        loadNavigationMap();

        if (performExtendedDiagnostics()) {  // Hook
            runExtendedDiagnostics();
        }

        signalReady();
    }

protected:
    // Concrete methods: Common to all robots
    void powerOnSelfTest() {
        std::cout << "Running Power-On Self-Test...\n";
        // Check CPU, memory, battery, etc.
    }

    void initializeCommunication() {
        std::cout << "Initializing WiFi and connecting to base station...\n";
    }

    void loadNavigationMap() {
        std::cout << "Loading navigation map from base station...\n";
    }

    void signalReady() {
        std::cout << "Robot ready for operation\n";
    }

    // Abstract methods: Hardware-specific
    virtual void calibrateSensors() = 0;
    virtual void initializeActuators() = 0;

    // Hook: Optional extended diagnostics
    virtual bool performExtendedDiagnostics() {
        return false;  // Default: skip
    }

    virtual void runExtendedDiagnostics() {
        // Default: do nothing
    }
};

// AMR-1000: Basic warehouse robot
class AMR1000Robot : public AutonomousRobot {
protected:
    void calibrateSensors() override {
        std::cout << "AMR-1000: Calibrating laser scanner...\n";
    }

    void initializeActuators() override {
        std::cout << "AMR-1000: Initializing differential drive...\n";
    }
};

// AMR-2000: Advanced robot with vision
class AMR2000Robot : public AutonomousRobot {
protected:
    void calibrateSensors() override {
        std::cout << "AMR-2000: Calibrating 3D LIDAR...\n";
        std::cout << "AMR-2000: Calibrating vision camera...\n";
    }

    void initializeActuators() override {
        std::cout << "AMR-2000: Initializing omni-directional drive...\n";
    }

    // Override hook: AMR-2000 has extended diagnostics
    bool performExtendedDiagnostics() override {
        return true;  // Always run for AMR-2000
    }

    void runExtendedDiagnostics() override {
        std::cout << "AMR-2000: Running extended vision system diagnostics...\n";
        std::cout << "AMR-2000: Testing fail-safe mechanisms...\n";
    }
};

// AMR-3000: Industrial robot with arm
class AMR3000Robot : public AutonomousRobot {
protected:
    void calibrateSensors() override {
        std::cout << "AMR-3000: Calibrating multi-sensor array...\n";
    }

    void initializeActuators() override {
        std::cout << "AMR-3000: Initializing mecanum drive...\n";
        std::cout << "AMR-3000: Initializing robotic arm and moving to home position...\n";
    }
};

// Client code
int main() {
    AMR1000Robot amr1000;
    AMR2000Robot amr2000;
    AMR3000Robot amr3000;

    std::cout << "=== AMR-1000 Startup ===\n";
    amr1000.startup();  // Same algorithm for all robots

    std::cout << "\n=== AMR-2000 Startup ===\n";
    amr2000.startup();  // Same algorithm, with extended diagnostics

    std::cout << "\n=== AMR-3000 Startup ===\n";
    amr3000.startup();  // Same algorithm, different hardware

    // BENEFITS:
    // 1. Algorithm defined once in base class
    // 2. Hardware-specific code only in subclasses
    // 3. Cannot change startup order accidentally
    // 4. Adding new robot? Just implement 2 methods
    // 5. Bug fix in algorithm? Fix once in base class
}
```

**Output:**

```text
=== AMR-1000 Startup ===
Running Power-On Self-Test...
Initializing WiFi and connecting to base station...
AMR-1000: Calibrating laser scanner...
AMR-1000: Initializing differential drive...
Loading navigation map from base station...
Robot ready for operation

=== AMR-2000 Startup ===
Running Power-On Self-Test...
Initializing WiFi and connecting to base station...
AMR-2000: Calibrating 3D LIDAR...
AMR-2000: Calibrating vision camera...
AMR-2000: Initializing omni-directional drive...
Loading navigation map from base station...
AMR-2000: Running extended vision system diagnostics...
AMR-2000: Testing fail-safe mechanisms...
Robot ready for operation

=== AMR-3000 Startup ===
Running Power-On Self-Test...
Initializing WiFi and connecting to base station...
AMR-3000: Calibrating multi-sensor array...
AMR-3000: Initializing mecanum drive...
AMR-3000: Initializing robotic arm and moving to home position...
Loading navigation map from base station...
Robot ready for operation
```

### Abstract Methods vs Hooks

**Abstract Methods (Pure Virtual):**

```cpp
// Subclass MUST implement
virtual void calibrateSensors() = 0;

// Use when: Step is required and varies between subclasses
```

**Hooks:**

```cpp
// Subclass CAN override (optional)
virtual bool performExtendedDiagnostics() {
    return false;  // Default behavior
}

// Use when: Step is optional or has sensible default
```

**Key Difference:**

- **Abstract method:** No default, subclass must provide implementation
- **Hook:** Has default, subclass can override if needed

**When to use each:**

```cpp
class CaffeineBeverage {
protected:
    // Abstract: Must brew (no default way to brew)
    virtual void brew() = 0;

    // Abstract: Must add condiments (no default condiments)
    virtual void addCondiments() = 0;

    // Hook: Default is "yes" to condiments
    // Subclass can override to ask user or return false
    virtual bool customerWantsCondiments() {
        return true;
    }

    // Concrete: Same for all beverages
    void boilWater() {
        std::cout << "Boiling water\n";
    }
};
```

---

## Benefits and Trade-offs

### Benefits

1. **Eliminates Code Duplication**
   - Algorithm defined once in base class
   - Common steps implemented once
   - Subclasses only implement varying parts
   - **Example:** `boilWater()` and `pourInCup()` in one place, not duplicated across Coffee/Tea/HotChocolate

2. **Enforces Algorithm Consistency**
   - Algorithm structure cannot be changed by subclasses
   - Guarantees all subclasses follow same sequence
   - Prevents accidental reordering of steps
   - **Safety:** Critical for safety-critical systems (robot startup, medical devices)

3. **Central Control of Algorithm**
   - Change algorithm once, affects all subclasses
   - Add new step: modify base class, all subclasses get it
   - Bug fix in algorithm: fix once
   - **Maintainability:** One place to update

4. **Easy to Add New Subclasses**
   ```cpp
   // Adding HotChocolate: Just implement 2 methods
   class HotChocolate : public CaffeineBeverage {
       void brew() override { std::cout << "Mixing chocolate\n"; }
       void addCondiments() override { std::cout << "Adding whipped cream\n"; }
   };
   // That's it! Algorithm already defined in base class
   ```

5. **Hollywood Principle (Inversion of Control)**
   - Framework (base class) calls you, not vice versa
   - Loose coupling between algorithm and implementation
   - Subclasses don't control flow
   - **Architectural benefit:** Clear separation of concerns

6. **Flexibility Through Hooks**
   - Optional extension points
   - Subclasses can customize behavior without breaking algorithm
   - Default behavior if hook not overridden
   - **Example:** `customerWantsCondiments()` hook allows Coffee to ask user, Tea to skip asking

7. **Protected Interface**
   - Template method is public (client interface)
   - Primitive operations are protected (subclass interface)
   - Clear separation of external and internal interfaces
   - **Encapsulation:** Clients can't call individual steps out of order

8. **Guaranteed Correctness**
   - Algorithm tested once in base class
   - Subclasses cannot break algorithm structure
   - Only subclass-specific steps need testing
   - **Testing:** Reduced testing surface area

### Trade-offs

1. **Inheritance-Based (Tight Coupling)**
   - Subclass tightly coupled to base class
   - Cannot use with unrelated classes
   - Violates "favor composition over inheritance" guideline
   - **Limitation:** Less flexible than Strategy pattern

   ```cpp
   // Cannot apply template method to existing class hierarchy
   class ExistingBeverage {  // Cannot retrofit template method
       // ... existing implementation
   };
   ```

2. **Rigid Algorithm Structure**
   - Cannot change algorithm order in subclasses
   - All subclasses must follow same structure
   - Not suitable if algorithms have different structures
   - **When inappropriate:** If Coffee needs 4 steps but Tea needs 6 steps in different order

3. **More Classes**
   - Every variant needs a subclass
   - Can lead to class explosion
   - **Example:** Coffee with milk, Coffee without milk → 2 classes
   - **Alternative:** Strategy pattern uses composition (fewer classes)

4. **Less Flexible Than Strategy Pattern**
   ```cpp
   // Template Method: Fixed at compile time
   Coffee coffee;  // Always a Coffee
   coffee.prepareRecipe();

   // Strategy Pattern: Can change at runtime
   CaffeineBeverage beverage(new CoffeeBrewing());
   beverage.prepareRecipe();
   beverage.setBrewingStrategy(new TeaBrewing());  // Change at runtime!
   beverage.prepareRecipe();
   ```

5. **Harder to Understand for Complex Algorithms**
   - Flow split between base class and subclasses
   - Must look at both to understand complete behavior
   - **Mitigation:** Good documentation, clear naming

6. **Fragile Base Class Problem**
   - Changes to base class affect all subclasses
   - Adding required abstract method breaks all subclasses
   - **Risk:** Maintenance risk if base class changes frequently

7. **Limited to Single Inheritance (C++)**
   - Cannot use template method if subclass already inherits from another class
   - **C++ specific:** Single inheritance limitation

### When to Use Template Method Pattern

✅ **Use Template Method when:**

- Multiple classes share same algorithm structure
- Algorithm steps are mostly the same, with few variations
- Want to enforce algorithm consistency across subclasses
- Need central control over algorithm
- Subclasses should not change algorithm structure
- Have clear invariant steps (common) and variant steps (specific)
- **Example scenarios:**
  - Initialization sequences (robot startup, device initialization)
  - Data processing pipelines (parse → process → output)
  - Test frameworks (setup → test → teardown)
  - Document generation (header → content → footer)

❌ **Don't use Template Method when:**

- Algorithms have completely different structures
- Need to change algorithm at runtime
- Want to mix and match algorithm steps dynamically
- Prefer composition over inheritance
- Don't have clear common structure
- **Alternative:** Use Strategy pattern for runtime flexibility

### Template Method vs Strategy Pattern

**Template Method:**

```cpp
// Algorithm structure fixed in base class
class CaffeineBeverage {
    void prepareRecipe() {
        boilWater();
        brew();      // Varies
        pourInCup();
        addCondiments();  // Varies
    }
};

// Pros: Enforces structure, no code duplication
// Cons: Compile-time fixed, requires inheritance
```

**Strategy Pattern:**

```cpp
// Algorithm steps encapsulated as strategies
class CaffeineBeverage {
    BrewingStrategy* brewing;
    CondimentsStrategy* condiments;

    void prepareRecipe() {
        boilWater();
        brewing->brew();
        pourInCup();
        condiments->add();
    }
};

// Pros: Runtime flexibility, composition
// Cons: More objects, doesn't enforce structure
```

**Choose Template Method when:** Structure consistency is priority (e.g., safety-critical systems)

**Choose Strategy when:** Runtime flexibility is priority (e.g., user-configurable behavior)

---

---

## Pattern Relationships

### Template Method vs Strategy Pattern

**Similarity:** Both allow varying parts of algorithm

**Difference:**

- **Template Method:** Uses inheritance, compile-time binding, fixed algorithm structure
- **Strategy:** Uses composition, runtime binding, flexible algorithm structure

**Template Method:**

```cpp
class CaffeineBeverage {
    void prepareRecipe() {  // Algorithm fixed
        boilWater();
        brew();           // Varies via inheritance
        pourInCup();
        addCondiments();  // Varies via inheritance
    }
};

class Coffee : public CaffeineBeverage {
    void brew() override { /* coffee brewing */ }
};
```

**Strategy:**

```cpp
class CaffeineBeverage {
    BrewingStrategy* strategy;

    void prepareRecipe() {  // Algorithm uses composition
        boilWater();
        strategy->brew();  // Varies via strategy object
        pourInCup();
    }

    void setStrategy(BrewingStrategy* s) {
        strategy = s;  // Can change at runtime!
    }
};
```

**When to choose:**

- **Template Method:** When algorithm structure is fixed and should not change
- **Strategy:** When need to change algorithm at runtime

### Template Method vs Factory Method

**Often used together:**

```cpp
class DocumentProcessor {
public:
    // Template method: Processing algorithm
    void processDocument() {
        Document* doc = createDocument();  // Factory method
        doc->open();
        parseContent(doc);
        doc->save();
        delete doc;
    }

protected:
    // Factory method: Create document
    virtual Document* createDocument() = 0;

    // Template method step
    virtual void parseContent(Document* doc) = 0;
};

class PDFProcessor : public DocumentProcessor {
protected:
    Document* createDocument() override {
        return new PDFDocument();  // Factory method
    }

    void parseContent(Document* doc) override {
        // PDF-specific parsing
    }
};
```

**Factory Method is often a step in Template Method.**

### Template Method in STL

C++ Standard Library uses template method pattern:

**Example 1: std::sort with custom comparator**

```cpp
// STL sort uses template method pattern
std::vector<int> numbers = {3, 1, 4, 1, 5};

// Default comparison (template method uses default step)
std::sort(numbers.begin(), numbers.end());

// Custom comparison (override "compare" step)
std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
    return a > b;  // Descending order
});

// Template method: sort algorithm fixed
// Varying step: comparison operation
```

**Example 2: std::unique_ptr custom deleter**

```cpp
// Template method: unique_ptr destruction algorithm
// Varying step: deleter operation

// Default deleter
std::unique_ptr<int> ptr1(new int(42));
// Uses default delete

// Custom deleter (override "delete" step)
auto deleter = [](int* p) {
    std::cout << "Custom delete\n";
    delete p;
};
std::unique_ptr<int, decltype(deleter)> ptr2(new int(42), deleter);
```

### Template Method + Hook = Framework Design

Frameworks heavily use template method with hooks:

```cpp
// Framework base class
class Application {
public:
    // Template method: Application lifecycle
    void run() {
        initialize();

        if (loadPlugins()) {  // Hook
            configurePlugins();
        }

        mainLoop();

        if (shouldSaveState()) {  // Hook
            saveState();
        }

        shutdown();
    }

protected:
    virtual void initialize() = 0;
    virtual void mainLoop() = 0;
    virtual void shutdown() = 0;

    // Hooks: Optional extension points
    virtual bool loadPlugins() { return false; }
    virtual void configurePlugins() { }
    virtual bool shouldSaveState() { return true; }
    virtual void saveState() { }
};

// User application
class MyApplication : public Application {
protected:
    void initialize() override { /* app-specific init */ }
    void mainLoop() override { /* app-specific loop */ }
    void shutdown() override { /* app-specific shutdown */ }

    // Override hooks for custom behavior
    bool loadPlugins() override { return true; }
    void configurePlugins() override { /* load specific plugins */ }
};
```

**Hollywood Principle in action:** Framework calls your code, you don't call framework.

### Template Method in Test Frameworks

```cpp
// Test framework uses template method
class TestCase {
public:
    // Template method: Test execution
    void runTest() {
        setUp();
        try {
            runTestBody();
        } catch (...) {
            tearDown();
            throw;
        }
        tearDown();
    }

protected:
    virtual void setUp() { }      // Hook: optional setup
    virtual void runTestBody() = 0;  // Abstract: test implementation
    virtual void tearDown() { }   // Hook: optional cleanup
};

// Concrete test
class MyTest : public TestCase {
protected:
    void setUp() override {
        // Test setup
    }

    void runTestBody() override {
        // Actual test
    }

    void tearDown() override {
        // Test cleanup
    }
};
```

---

## Summary: The Power of Template Method Pattern

**Before Template Method Pattern:**

- Algorithm structure duplicated across multiple classes
- Common steps duplicated (code duplication)
- Cannot enforce algorithm consistency
- Changes require modifying all classes
- Risk of accidental algorithm variation
- Maintenance nightmare

**After Template Method Pattern:**

- ✅ **Algorithm Defined Once:** Single definition in base class
- ✅ **No Code Duplication:** Common steps implemented once
- ✅ **Enforced Consistency:** Subclasses cannot change algorithm structure
- ✅ **Central Control:** Algorithm changes in one place
- ✅ **Easy Extension:** New subclasses implement only varying parts
- ✅ **Hollywood Principle:** Framework calls subclass, not vice versa
- ✅ **Hooks for Flexibility:** Optional extension points

**Architectural Thinking:**

When you have **multiple classes that follow the same algorithm structure** but with different implementations for specific steps, **DON'T** duplicate the algorithm. Instead, **extract the algorithm structure into a base class template method** and let subclasses provide implementations for varying steps. This is the essence of **algorithmic reuse through inheritance**.

**Real-World Impact:**

In the robot initialization example, Template Method Pattern enables:
- Startup sequence defined once in base class (50 lines)
- Subclasses implement only hardware-specific steps (10 lines each)
- Adding new robot model: 10 lines, not 50 lines
- Algorithm change affects all robots immediately
- Cannot accidentally change startup order
- Safety-critical: Guaranteed consistent initialization

This transforms a maintenance nightmare (duplicated algorithms) into a clean, maintainable, safe system.

**Key Design Insight:**

Template Method is about **code reuse through inheritance** and **protecting algorithm invariants**. Use it when you need **consistency** and **central control**. If you need **flexibility** and **runtime behavior changes**, use Strategy pattern instead.

**Hollywood Principle - "Don't Call Us, We'll Call You":**

The base class (framework) controls the algorithm flow and calls subclass methods at appropriate times. Subclasses don't control when their methods are called—the template method does. This inversion of control is fundamental to framework design.

---

## References

- **Design Principles:** Hollywood Principle (Inversion of Control), DRY (Don't Repeat Yourself), Open/Closed Principle, Liskov Substitution, Single Responsibility
- **C++ Features:** Virtual functions, pure virtual (abstract), NVI idiom, final keyword, CRTP, smart pointers, virtual destructor
- **Related Patterns:** Strategy (runtime variation), Factory Method (often combined), Hook (extension point)
- **Real-World Applications:** Framework design, initialization sequences, test frameworks, data processing pipelines, document generation, game AI behavior trees
