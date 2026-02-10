# Decorator Pattern - Starbuzz Coffee Analysis

## Pattern Overview

**Name:** Decorator Pattern (Structural Pattern)

**Intent:** Attach additional responsibilities to an object dynamically. Decorators provide a flexible alternative to subclassing for extending functionality.

**Also Known As:** Wrapper

---

## 1. The Problem - Show the Pain! 💥

### The Nightmare: Class Explosion or Rigid Inheritance

Imagine you're building a coffee ordering system for Starbuzz Coffee. You have different beverages (Espresso, House Blend, Dark Roast) and various condiments (Milk, Mocha, Soy, Whip). Customers can order any beverage with any combination of condiments.

#### Bad Approach #1: Inheritance Explosion

```cpp
// BAD ARCHITECTURE - Class Explosion
class Beverage {
public:
    virtual double cost() = 0;
    virtual std::string getDescription() = 0;
};

class Espresso : public Beverage { /* ... */ };
class HouseBlend : public Beverage { /* ... */ };

// Now add condiments... EXPLOSION!
class EspressoWithMocha : public Beverage { /* ... */ };
class EspressoWithMochaAndWhip : public Beverage { /* ... */ };
class EspressoWithSoy : public Beverage { /* ... */ };
class EspressoWithSoyAndMocha : public Beverage { /* ... */ };
class EspressoWithSoyAndMochaAndWhip : public Beverage { /* ... */ };

class HouseBlendWithMocha : public Beverage { /* ... */ };
class HouseBlendWithMochaAndWhip : public Beverage { /* ... */ };
// ... 🤯 HUNDREDS OF CLASSES!
```

**Problem:** With 4 beverages and 4 condiments, you need:
- 4 base classes
- 4 × 4 = 16 (beverage + single condiment)
- 4 × (4 choose 2) = 24 (beverage + two condiments)
- 4 × (4 choose 3) = 16 (beverage + three condiments)
- 4 × 1 = 4 (beverage + all four condiments)

**Total: 64 classes!** And that's just for 4 condiments. Add one more condiment? Double the classes!

#### Bad Approach #2: Boolean Flags in Base Class

```cpp
// BAD ARCHITECTURE - Inflexible Flags
class Beverage {
protected:
    bool hasMilk;
    bool hasMocha;
    bool hasSoy;
    bool hasWhip;
    double milkCost = 0.10;
    double mochaCost = 0.20;
    double soyCost = 0.15;
    double whipCost = 0.10;

public:
    virtual double cost() {
        double total = baseCost();
        if (hasMilk) total += milkCost;
        if (hasMocha) total += mochaCost;
        if (hasSoy) total += soyCost;
        if (hasWhip) total += whipCost;
        return total;
    }

    virtual double baseCost() = 0;

    void setMilk(bool milk) { hasMilk = milk; }
    void setMocha(bool mocha) { hasMocha = mocha; }
    // ... more setters
};

class Espresso : public Beverage {
public:
    double baseCost() override { return 1.99; }
};
```

### What's Wrong Here? The Pain Points

#### 1. **Violates Open/Closed Principle**

**New requirement:** "Add a new condiment: Caramel!"

You must:
- Modify the `Beverage` base class (add `hasCaramel`, `caramelCost`)
- Modify the `cost()` method
- Recompile ALL beverage classes

**Every new feature requires modifying existing code!**

#### 2. **Inflexible Pricing**

What if condiment prices vary by beverage?
- Double mocha in Espresso costs more than in House Blend?
- Large sizes get more expensive condiments?

**The boolean flag approach can't handle this!**

#### 3. **No Multiple Quantities**

Customer wants "double mocha" or "triple whip"? With boolean flags, you're stuck:

```cpp
bool hasDoubleMocha;  // Now we need MORE flags!
bool hasTripleMocha;  // This is getting ridiculous
```

#### 4. **Hard to Test**

Testing beverage with specific condiment combinations requires setting multiple flags:

```cpp
Espresso esp;
esp.setMocha(true);
esp.setWhip(true);
// Fragile - easy to forget a flag
```

#### 5. **Maintenance Nightmare**

Six months later, new developer looks at code:
- "Which condiments does this beverage have?"
- "How do I add a seasonal condiment?"
- "Why are there 20 boolean flags in the base class?"

### Design Principles Violated

- ❌ **Open/Closed Principle** - Must modify Beverage to add new condiments
- ❌ **Single Responsibility** - Beverage manages both beverage logic AND condiment logic
- ❌ **Composition over Inheritance** - Using inheritance for feature combinations
- ❌ **Encapsulate what varies** - Condiments are hardcoded in base class

---

## 2. Real-World Example: Embedded Device Drivers 🔧

**Scenario:** You're building device drivers for an embedded microcontroller that interfaces with UART (serial) hardware. Different projects need different features:

### Bad Inheritance/Flag Approach

```cpp
class UARTDriver {
protected:
    bool enableLogging;
    bool enableCRC;
    bool enableBuffering;
    bool enableEncryption;

public:
    void send(uint8_t* data, size_t len) {
        // Check all flags...
        if (enableLogging) { /* log data */ }
        if (enableCRC) { /* calculate CRC */ }
        if (enableBuffering) { /* buffer data */ }
        if (enableEncryption) { /* encrypt data */ }

        // Actually send to hardware
        sendToHardware(data, len);
    }

    // Setters for all flags...
    void setLogging(bool enable) { enableLogging = enable; }
    void setCRC(bool enable) { enableCRC = enable; }
    // ...
};
```

**Problems in Production:**

1. **Memory Constraints**: Each flag adds memory overhead, even if unused
   - Product A: Needs only logging → wasting memory on CRC/encryption code
   - Product B: Needs only CRC → wasting memory on logging/encryption code

2. **Code Bloat**: Base driver includes ALL features, even if only 1 is used
   - Embedded systems have limited flash memory (32KB, 64KB)
   - Including unused code is wasteful

3. **Conditional Compilation Hell**:

   ```cpp
   #ifdef ENABLE_LOGGING
       if (enableLogging) { /* log */ }
   #endif
   #ifdef ENABLE_CRC
       if (enableCRC) { /* CRC */ }
   #endif
   // Preprocessor nightmare!
   ```

4. **New Feature = Modify Driver**: "Add DMA support!"
   - Modify `UARTDriver` base class
   - Add `enableDMA` flag
   - Modify `send()` method
   - **Risk breaking existing products!**

5. **Performance Overhead**: Every `send()` call checks multiple flags
   - In interrupt service routines (ISRs), every cycle counts
   - Flag checks add latency

**Real-World Impact:**

- **Bloated firmware** - wasting precious flash memory
- **Fragile updates** - changing driver breaks existing products
- **Poor performance** - unnecessary flag checks in hot paths
- **Difficult customization** - each customer needs custom build

**This is exactly the pain the Decorator pattern solves!**

---

## 3. The Solution - The Insight 💡

### The Key Architectural Insight

**"Wrap objects with decorator objects that add behavior dynamically. Decorators have the SAME interface as the objects they wrap, so clients can't tell the difference."**

Instead of modifying the base class or creating subclasses for every combination, **wrap** the core object with layers of decorators, each adding one responsibility.

**The Trick:**

1. **Component interface** - Defines the common interface (e.g., `Beverage`)
2. **Concrete components** - Core objects (e.g., `Espresso`, `HouseBlend`)
3. **Decorator base class** - Wraps a component, has same interface
4. **Concrete decorators** - Add specific responsibilities (e.g., `Mocha`, `Whip`)
5. **Decorators delegate** - Call wrapped object's methods, add own behavior before/after

### The Decorator Pattern Structure

```text
Component (Interface/Abstract)
├── operation()

ConcreteComponent
├── implements Component
└── operation()

Decorator (Abstract)
├── implements Component
├── HAS-A Component* wrappedObj
└── operation() { wrappedObj->operation(); }

ConcreteDecoratorA
├── extends Decorator
└── operation() { addBehaviorBefore(); wrappedObj->operation(); addBehaviorAfter(); }

ConcreteDecoratorB
├── extends Decorator
└── operation() { wrappedObj->operation(); addOwnBehavior(); }
```

**Key:** Decorators wrap components, but ARE-A component too (same interface).

### Side-by-Side: Before vs After

| Aspect | Inheritance/Flags (Before) | Decorator Pattern (After) |
|--------|----------------------------|---------------------------|
| **Adding Feature** | Modify base class or add subclass | Create new decorator |
| **Combinations** | Exponential class explosion | Compose decorators at runtime |
| **Flexibility** | Compile-time features | Runtime wrapping |
| **Code Changes** | Modify existing classes | Add new decorator (Open/Closed) |
| **Testing** | Test all combinations | Test each decorator independently |
| **Multiple Quantities** | Need more flags (hasDouble, hasTriple) | Wrap multiple times: `new Mocha(new Mocha(espresso))` |

### Starbuzz Coffee Example

```cpp
// Base component
Beverage* beverage = new Espresso();  // $1.99

// Wrap with decorators
beverage = new Mocha(beverage);       // $1.99 + $0.20 = $2.19
beverage = new Mocha(beverage);       // $2.19 + $0.20 = $2.39 (double mocha!)
beverage = new Whip(beverage);        // $2.39 + $0.10 = $2.49

std::cout << beverage->getDescription();  // "Espresso, Mocha, Mocha, Whip"
std::cout << beverage->cost();            // $2.49
```

**How it works:**

1. `beverage->cost()` calls `Whip::cost()`
2. `Whip::cost()` returns `0.10 + wrappedBeverage->cost()`
3. Calls second `Mocha::cost()` → `0.20 + wrappedBeverage->cost()`
4. Calls first `Mocha::cost()` → `0.20 + wrappedBeverage->cost()`
5. Calls `Espresso::cost()` → `1.99`
6. **Total:** `1.99 + 0.20 + 0.20 + 0.10 = 2.49`

---

## 4. The Principles - The "Why" 🎯

### Design Principles Demonstrated

#### 1. **Open/Closed Principle (The Star of the Show!)**

**Open for extension:** Add new decorators without modifying existing classes

```cpp
// New condiment? Just create a decorator!
class Caramel : public CondimentDecorator {
    Beverage* beverage;
public:
    Caramel(Beverage* b) : beverage(b) {}
    double cost() override { return 0.25 + beverage->cost(); }
    std::string getDescription() override {
        return beverage->getDescription() + ", Caramel";
    }
};

// Use it immediately - no changes to Beverage or Espresso!
Beverage* b = new Caramel(new Espresso());
```

**Closed for modification:** Existing classes (Beverage, Espresso, Mocha) never change.

#### 2. **Single Responsibility Principle**

**Before:**

- `Beverage` class responsible for:
  - Beverage properties (description)
  - Beverage cost calculation
  - **AND** condiment management (flags, costs)
  - **AND** condiment cost calculation

**After:**

- `Beverage`: Beverage interface only
- `Espresso`: Espresso-specific logic only
- `Mocha` decorator: Mocha-specific logic only
- Each class has ONE reason to change

#### 3. **Composition Over Inheritance**

**Before (Inheritance):** `EspressoWithMocha extends Espresso`
- Compile-time binding
- Rigid structure

**After (Composition):** `Mocha HAS-A Beverage`
- Runtime binding
- Flexible wrapping

#### 4. **Decorators ARE-A Component AND HAS-A Component**

This is the clever part:

```cpp
class Mocha : public Beverage {  // IS-A Beverage
    Beverage* beverage;           // HAS-A Beverage
};
```

**Why?**

- **IS-A**: So decorators can be used anywhere a Beverage is expected
- **HAS-A**: So decorators can wrap and delegate to the wrapped object

**Result:** Transparent wrapping - client can't tell if it's a core component or a decorator!

### Architectural Thinking Process

**As an architect, I see this problem:**

"We need to add features (condiments) to core objects (beverages) in arbitrary combinations. Inheritance creates exponential classes. Flags make the base class bloated and inflexible."

**This violates principles because:**

- Every new feature requires modifying the base class (violates Open/Closed)
- Base class has multiple responsibilities (violates SRP)
- Features are compile-time (inflexible)

**If we introduce the Decorator pattern, we gain:**

- **Extensibility:** Add features without modifying existing code
- **Flexibility:** Compose features at runtime
- **Single Responsibility:** Each decorator handles one feature
- **Testability:** Test decorators in isolation

**The trade-off is:**

- More classes (but small, focused ones)
- Indirection (wrapped layers)
- Worth it when feature combinations grow or change frequently

---

## 5. The Benefits - What You Gain ✅

### Flexibility: What Becomes Easy to Change?

1. **Add New Features - Zero Existing Code Changes**

   ```cpp
   // New seasonal condiment
   class PumpkinSpice : public CondimentDecorator {
       Beverage* beverage;
   public:
       PumpkinSpice(Beverage* b) : beverage(b) {}
       double cost() override { return 0.30 + beverage->cost(); }
       std::string getDescription() override {
           return beverage->getDescription() + ", Pumpkin Spice";
       }
   };

   // Use immediately!
   Beverage* seasonal = new PumpkinSpice(new Espresso());
   // Existing classes UNCHANGED!
   ```

2. **Multiple Quantities Naturally**

   ```cpp
   // Double mocha? Just wrap twice!
   Beverage* b = new Espresso();
   b = new Mocha(b);
   b = new Mocha(b);  // Second mocha
   ```

3. **Any Combination at Runtime**

   ```cpp
   Beverage* custom = new Espresso();
   custom = new Mocha(custom);
   custom = new Soy(custom);
   custom = new Whip(custom);
   custom = new Mocha(custom);  // Extra mocha!
   // Any order, any quantity!
   ```

4. **Different Feature Sets Per Object**

   ```cpp
   Beverage* simple = new HouseBlend();
   Beverage* fancy = new Whip(new Mocha(new Soy(new Espresso())));
   // Two different objects, different features, same type!
   ```

### Maintainability: Easier to Understand/Debug

- **Small, Focused Classes:** Each decorator does ONE thing
- **Clear Responsibility:** Look at `Mocha` class to understand mocha behavior
- **Localized Changes:** Bug in whip cost? Fix `Whip` class only
- **No Coupling:** Decorators don't know about each other

### Testability: Isolated Testing

```cpp
// Test Mocha decorator independently
TEST(MochaTest, AddsCorrectCost) {
    MockBeverage* mock = new MockBeverage(1.00);  // Base cost
    Mocha* mocha = new Mocha(mock);
    ASSERT_EQ(mocha->cost(), 1.20);  // 1.00 + 0.20
}

// Test stacking
TEST(DecoratorTest, MultipleDecorators) {
    Beverage* b = new Espresso();  // 1.99
    b = new Mocha(b);              // +0.20
    b = new Whip(b);               // +0.10
    ASSERT_EQ(b->cost(), 2.29);
}
```

### Real-World Impact: Production Systems

**Embedded Device Driver Example (continued):**

With Decorator pattern:

```cpp
class UARTDriver {  // Base component
public:
    virtual void send(uint8_t* data, size_t len) {
        sendToHardware(data, len);  // Core functionality only
    }
};

class LoggingDecorator : public UARTDriver {
    UARTDriver* driver;
public:
    void send(uint8_t* data, size_t len) override {
        logData(data, len);  // Add logging
        driver->send(data, len);  // Delegate
    }
};

class CRCDecorator : public UARTDriver {
    UARTDriver* driver;
public:
    void send(uint8_t* data, size_t len) override {
        uint8_t* dataWithCRC = appendCRC(data, len);
        driver->send(dataWithCRC, len + 2);  // Add CRC, delegate
    }
};

// Product A: Only logging
UARTDriver* driverA = new LoggingDecorator(new UARTDriver());

// Product B: Only CRC
UARTDriver* driverB = new CRCDecorator(new UARTDriver());

// Product C: Both features
UARTDriver* driverC = new LoggingDecorator(
    new CRCDecorator(new UARTDriver())
);

// Each product includes ONLY the features it needs!
// No wasted memory, no unused code
```

**Key Production Benefits:**

- **Minimal memory footprint** - Only include features you use
- **Modular features** - Add/remove without touching base driver
- **Build variants** - Different products get different decorator combinations
- **Performance** - No flag checking, direct calls only
- **Maintainability** - Each feature isolated in its own decorator

---

## 6. The Trade-offs - Be Honest ⚖️

### Added Complexity

**More Classes:**

- Before: 1 `Beverage` + 4 concrete beverages = 5 classes
- After: 1 `Beverage` + 1 `CondimentDecorator` + 4 beverages + 4 condiments = 10 classes

**But:** Classes are small, focused, easy to understand. Better than 64 combination classes!

**Indirection/Wrapping:**

- Before: Direct call `espresso.cost()`
- After: Chain of calls through decorators: `Whip::cost()` → `Mocha::cost()` → `Espresso::cost()`

### Potential Issues

#### 1. **Identity Problems**

Decorators change the object's type (from client's perspective):

```cpp
Beverage* b = new Espresso();
Espresso* esp = dynamic_cast<Espresso*>(b);  // OK

b = new Mocha(b);  // Wrap with Mocha
esp = dynamic_cast<Espresso*>(b);  // NULL! It's a Mocha now
```

**Mitigation:** Don't rely on concrete types; use the component interface.

#### 2. **Order Matters (Sometimes)**

```cpp
// Logging before encryption
UARTDriver* d1 = new EncryptionDecorator(new LoggingDecorator(base));
// Logs plaintext, then encrypts

// Encryption before logging
UARTDriver* d2 = new LoggingDecorator(new EncryptionDecorator(base));
// Encrypts first, then logs ciphertext

// Different behavior!
```

#### 3. **Debugging Can Be Confusing**

When debugging, stack traces show multiple decorator layers:

```text
Whip::cost()
  -> Mocha::cost()
    -> Mocha::cost()
      -> Espresso::cost()
```

New developers might find this confusing.

#### 4. **Memory Management (C++)**

Who owns the wrapped objects?

```cpp
Beverage* b = new Espresso();
b = new Mocha(b);  // Mocha now wraps Espresso
b = new Whip(b);   // Whip now wraps Mocha

delete b;  // What gets deleted?
```

**Solution:** Use smart pointers (see C++ Considerations section).

### When Might This Be Overkill?

**DON'T use Decorator when:**

1. **No feature combinations needed**
   - If customers can only choose ONE condiment, simple inheritance suffices
   - Example: "Choose milk OR soy OR nothing"

2. **Features don't compose**
   - If features conflict or don't work together
   - Decorator assumes features can be stacked

3. **Few features, rarely change**
   - 2-3 features that never change? Boolean flags might be simpler
   - Decorator shines when features grow or change frequently

4. **Performance is critical**
   - Virtual function calls through multiple layers add overhead
   - Embedded real-time systems with nanosecond budgets

### When You SHOULD Use This

✅ Multiple independent features that can be combined
✅ Features added at runtime (not compile-time)
✅ Avoid class explosion from feature combinations
✅ New features added frequently
✅ Features should be optional and composable
✅ Need to support any combination of features

---

## 7. C++ Considerations - Language Mapping 🔧

### Java vs C++: Key Differences

| Aspect | Java | C++ |
|--------|------|-----|
| **Memory Management** | Garbage collected | Manual (use smart pointers!) |
| **Ownership** | GC handles it | Decorator must manage wrapped object lifetime |
| **Polymorphism** | All virtual by default | Explicit `virtual` keyword |
| **Return Types** | Can use primitives directly | Same, but watch object slicing |

### Modern C++ Advantages

#### 1. **Smart Pointers for Ownership**

**Problem:** Who deletes the wrapped objects?

```cpp
// BAD: Memory leak!
Beverage* b = new Espresso();
b = new Mocha(b);  // Mocha wraps Espresso
b = new Whip(b);   // Whip wraps Mocha
delete b;          // Only deletes Whip! Mocha and Espresso leaked!
```

**Solution: `std::unique_ptr` with Move Semantics**

```cpp
class Mocha : public Beverage {
    std::unique_ptr<Beverage> beverage;  // Owns the wrapped object

public:
    Mocha(std::unique_ptr<Beverage> b) : beverage(std::move(b)) {}

    double cost() override {
        return 0.20 + beverage->cost();
    }
};

// Usage:
auto b = std::make_unique<Espresso>();
b = std::make_unique<Mocha>(std::move(b));  // Transfer ownership
b = std::make_unique<Whip>(std::move(b));   // Transfer ownership

// When 'b' goes out of scope, entire chain is deleted automatically!
```

**Why `unique_ptr`?**

- Decorator exclusively owns the wrapped object (no sharing)
- Move semantics = zero overhead
- RAII: automatic cleanup

#### 2. **Const Correctness**

```cpp
class Beverage {
public:
    virtual double cost() const = 0;  // Doesn't modify state
    virtual std::string getDescription() const = 0;
    virtual ~Beverage() = default;
};

class Mocha : public Beverage {
    std::unique_ptr<Beverage> beverage;

public:
    double cost() const override {  // Can call on const Mocha
        return 0.20 + beverage->cost();
    }
};
```

#### 3. **Virtual Destructor (Critical!)**

```cpp
class Beverage {
public:
    virtual double cost() const = 0;
    virtual ~Beverage() = default;  // MUST be virtual!
};
```

**Why?**

```cpp
Beverage* b = new Mocha(new Espresso());
delete b;  // Without virtual destructor: only ~Beverage() called!
           // Espresso leaks!
```

#### 4. **Move-Only Decorator for Performance**

```cpp
class Mocha : public Beverage {
    std::unique_ptr<Beverage> beverage;

public:
    // Move constructor
    Mocha(std::unique_ptr<Beverage> b) : beverage(std::move(b)) {}

    // Move-only (no copying expensive decorator chains)
    Mocha(Mocha&&) = default;
    Mocha& operator=(Mocha&&) = default;
    Mocha(const Mocha&) = delete;
    Mocha& operator=(const Mocha&) = delete;
};
```

#### 5. **Builder Pattern for Readability**

Decorator chains can be hard to read. Use a builder:

```cpp
class BeverageBuilder {
    std::unique_ptr<Beverage> beverage;

public:
    BeverageBuilder& withBase(std::unique_ptr<Beverage> b) {
        beverage = std::move(b);
        return *this;
    }

    BeverageBuilder& addMocha() {
        beverage = std::make_unique<Mocha>(std::move(beverage));
        return *this;
    }

    BeverageBuilder& addWhip() {
        beverage = std::make_unique<Whip>(std::move(beverage));
        return *this;
    }

    std::unique_ptr<Beverage> build() {
        return std::move(beverage);
    }
};

// Usage:
auto beverage = BeverageBuilder()
    .withBase(std::make_unique<Espresso>())
    .addMocha()
    .addMocha()  // Double mocha!
    .addWhip()
    .build();
```

#### 6. **Template Decorators (Advanced)**

For zero-overhead decorators:

```cpp
template<typename Component>
class LoggingDecorator : public Component {
public:
    void operation() {
        std::cout << "Logging...\n";
        Component::operation();
    }
};

// Usage:
using LoggedEspresso = LoggingDecorator<Espresso>;
```

**Trade-off:** No runtime wrapping, but compile-time type explosion.

---

## 8. Implementation Details

### Class Structure

```text
Beverage (abstract component)
├── getDescription() : string
└── cost() : double

ConcreteComponent (Espresso, HouseBlend, DarkRoast, Decaf)
├── extends Beverage
└── implements cost(), getDescription()

CondimentDecorator (abstract decorator)
├── extends Beverage
├── HAS-A Beverage* wrappedBeverage
└── getDescription() : string (abstract)

ConcreteDecorator (Mocha, Whip, Soy)
├── extends CondimentDecorator
├── HAS-A Beverage* wrappedBeverage
└── cost() { return condimentCost + wrappedBeverage->cost(); }
└── getDescription() { return wrappedBeverage->getDescription() + ", Condiment"; }
```

### Key Relationships

1. **Decorator IS-A Component** - Enables transparent wrapping
2. **Decorator HAS-A Component** - Enables delegation
3. **Decorators can wrap other decorators** - Recursive structure

---

## 9. Key Takeaways

### For a Software Architect

1. **Open/Closed Principle in Action**
   - Add new decorators without modifying existing code
   - Extend functionality without inheritance explosion

2. **Composition + Polymorphism = Flexibility**
   - Decorators wrap components via composition
   - Polymorphism makes wrapping transparent

3. **Single Responsibility**
   - Each decorator handles ONE concern
   - Base component is simple, focused

4. **Runtime Flexibility**
   - Assemble features at runtime
   - Any combination, any order

### When to Apply

- Multiple optional features that can be combined
- Need to avoid class explosion from feature combinations
- Features added/removed at runtime
- Features are independent and composable
- Open/Closed Principle is critical (frequent feature additions)

### Anti-Patterns to Avoid

- ❌ Using Decorator when features don't compose (conflict)
- ❌ Forgetting virtual destructor in C++
- ❌ Not managing wrapped object lifetime (memory leaks)
- ❌ Relying on concrete types after wrapping (identity problem)
- ❌ Using Decorator for mutually exclusive options (use Strategy instead)

---

## 10. Comparison to Related Patterns

### Decorator vs Strategy

- **Decorator:** Adds responsibilities, wraps objects
- **Strategy:** Changes algorithm/behavior, replaces internals
- Decorator = "add features", Strategy = "swap behavior"

### Decorator vs Proxy

- **Decorator:** Adds functionality
- **Proxy:** Controls access (lazy loading, access control, remote proxy)
- Similar structure, different intent

### Decorator vs Composite

- **Decorator:** Adds to individual objects
- **Composite:** Organizes objects into tree structures
- Both use recursive composition, different purposes

---

## 11. Real-World Use Cases

### Embedded Systems 🔧

```cpp
// UART driver with optional features
UARTDriver* driver = new UARTDriver();
driver = new BufferingDecorator(driver);    // Add buffering
driver = new CRCDecorator(driver);          // Add error checking
driver = new LoggingDecorator(driver);      // Add logging
// Only include features you need!
```

### Java I/O Streams (Classic Example)

```java
InputStream in = new FileInputStream("file.txt");
in = new BufferedInputStream(in);       // Add buffering
in = new DataInputStream(in);            // Add data type reading
// Stack decorators for different features
```

### GUI Widgets

```cpp
Window* window = new SimpleWindow();
window = new ScrollbarDecorator(window);  // Add scrollbar
window = new BorderDecorator(window);     // Add border
// Compose visual features
```

### Network Middleware

```cpp
RequestHandler* handler = new CoreHandler();
handler = new AuthDecorator(handler);       // Add authentication
handler = new LoggingDecorator(handler);    // Add logging
handler = new RateLimitDecorator(handler);  // Add rate limiting
// Middleware pipeline
```

---

## Conclusion

The Decorator Pattern is your architectural answer to **"How do I add features to objects without creating a class explosion?"**

**Core Insight:** Wrap objects with decorators that add behavior transparently. Decorators have the same interface as wrapped objects, enabling recursive composition.

**Remember:** Use this pattern when you need flexible feature combinations that can be added at runtime. The added classes are small and focused, avoiding the explosion of combination subclasses.

**Next Steps:** Look at the C++ implementation to see these principles in action with modern C++20 features and smart pointers!
