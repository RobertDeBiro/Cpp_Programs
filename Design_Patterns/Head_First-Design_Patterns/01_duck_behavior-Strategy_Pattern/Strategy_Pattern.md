# Strategy Pattern - Duck Behavior Analysis

---

## Pattern Overview

**Name:** Strategy Pattern (Behavioral Pattern)

**Intent:** Define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

**Also Known As:** Policy Pattern

---

## The Problem - Show the Pain! 💥

### The Nightmare: Inheritance-Based Design

Imagine you're building a duck simulation game. Your first instinct as a developer might be to use inheritance:

```cpp
// BAD ARCHITECTURE - Inheritance Hell
class Duck {
public:
    virtual void quack() {
        std::cout << "Quack!\n";
    }

    virtual void fly() {
        std::cout << "I'm flying!\n";
    }

    virtual void display() = 0;  // Different for each duck type

    void swim() {
        std::cout << "All ducks float!\n";
    }
};

class MallardDuck : public Duck {
public:
    void display() override {
        std::cout << "I'm a Mallard duck\n";
    }
};

class RubberDuck : public Duck {
public:
    void display() override {
        std::cout << "I'm a rubber duck\n";
    }

    // Problem 1: Rubber ducks don't fly!
    void fly() override {
        // Do nothing or print error?
        std::cout << "I can't fly!\n";
    }

    // Problem 2: Rubber ducks squeak, not quack!
    void quack() override {
        std::cout << "Squeak!\n";
    }
};

class DecoyDuck : public Duck {
public:
    void display() override {
        std::cout << "I'm a decoy duck\n";
    }

    // Problem 3: Decoys don't fly OR quack!
    void fly() override {
        // Silent or error?
    }

    void quack() override {
        // Silent or error?
    }
};
```

### What's Wrong Here? The Pain Points

#### 1. **Code Duplication**

Multiple duck types need the same "can't fly" behavior. You're copying `fly() { /* do nothing */ }` everywhere!

#### 2. **Rigid Structure - Violates Open/Closed Principle**

**Requirement change:** "Add rocket-powered flight for model ducks!"

You'd have to:

- Modify the base `Duck` class (scary!)
- Or add a new method `flyWithRocket()` (code smell - method explosion)
- Every time you add a new behavior variant, you touch existing code

#### 3. **Inheritance Misuse - "IS-A" Doesn't Fit**

- A RubberDuck "IS-A" Duck (conceptually yes)
- But it doesn't inherit the right behaviors (flies, quacks)
- **Inheritance gives you ALL behaviors, whether you want them or not!**

#### 4. **Runtime Flexibility? Impossible!**

**New requirement:** "Let ducks change their flying ability at runtime!"

With inheritance, a duck's behavior is **locked at compile time**. You can't swap a duck's flying ability from "fly with wings" to "rocket-powered" dynamically.

#### 5. **Testing Nightmare**

To test flying behavior, you must instantiate a concrete duck. Can't test the flying logic in isolation.

### Design Principles Violated

- ❌ **Encapsulate what varies** - Behaviors (fly, quack) are NOT encapsulated; they're hardcoded in subclasses
- ❌ **Favor composition over inheritance** - Using inheritance for behavior reuse
- ❌ **Program to interfaces** - Clients depend on concrete Duck classes
- ❌ **Open/Closed Principle** - Adding new behaviors requires modifying existing classes

### UML Diagram: Bad Design

See `UML/Bad_Inheritance_Design.puml` for the class diagram showing the inheritance-based approach with its problems (red-highlighted problem classes).

---

## The Solution - The Insight 💡

### The Key Architectural Insight

**Take what varies and encapsulate it so it won't affect the rest of your code.**

Instead of duck *inheriting* behavior (IS-A), give each duck *references* to behavior objects (HAS-A).

**The Trick:**

1. **Extract varying behaviors** into separate class hierarchies
2. **Program to interfaces** (FlyBehavior, QuackBehavior), not implementations
3. **Compose** ducks with behaviors at runtime using **delegation**

### The Strategy Pattern Structure

```bash
Duck
├── HAS-A FlyBehavior (interface)
│   ├── FlyWithWings (concrete strategy)
│   ├── FlyNoWay (concrete strategy)
│   └── FlyRocketPowered (concrete strategy)
└── HAS-A QuackBehavior (interface)
    ├── Quack (concrete strategy)
    ├── Squeak (concrete strategy)
    └── MuteQuack (concrete strategy)
```

### Side-by-Side: Before vs After

| Aspect | Inheritance (Before) | Strategy Pattern (After) |
|--------|---------------------|--------------------------|
| **Behavior Location** | Hardcoded in each subclass | Encapsulated in strategy objects |
| **Behavior Reuse** | Copy-paste or complex inheritance | Compose with any strategy |
| **Runtime Changes** | Impossible | `duck.setFlyBehavior(new FlyRocketPowered())` |
| **Testing** | Must instantiate full duck | Test strategies in isolation |
| **Adding New Behavior** | Modify subclasses | Create new strategy class |
| **Relationship** | Duck IS-A FlyingThing (wrong) | Duck HAS-A FlyBehavior (correct) |

---

## The Principles - The "Why" 🎯

### Design Principles Demonstrated

#### 1. **Encapsulate What Varies**

**What varies?** Flying and quacking behaviors change between duck types.

**Solution:** Extract them into separate class hierarchies (`FlyBehavior`, `QuackBehavior`).

**Result:** Changes to flying logic don't touch `Duck` or any other behavior.

#### 2. **Favor Composition Over Inheritance (HAS-A > IS-A)**

**Before:** Duck IS-A FlyingThing → rigid, compile-time binding

**After:** Duck HAS-A FlyBehavior → flexible, runtime binding

**Why it matters:**

- Inheritance = "white-box reuse" (subclass knows parent internals)
- Composition = "black-box reuse" (no knowledge of internals)
- Composition allows **mixing and matching** behaviors

#### 3. **Program to Interfaces, Not Implementations**

**The Duck class doesn't know about `FlyWithWings` or `FlyNoWay`:**

```cpp
class Duck {
    FlyBehavior* flyBehavior;  // Interface pointer, not concrete type!

    void performFly() {
        flyBehavior->fly();  // Delegation - don't care HOW it flies
    }
};
```

**Benefits:**

- Duck is **decoupled** from concrete behaviors
- Can swap in new strategies without changing Duck
- **Polymorphism** handles the rest

#### 4. **Dependency Inversion Principle**

**High-level module** (`Duck`) doesn't depend on **low-level modules** (`FlyWithWings`).

Both depend on **abstraction** (`FlyBehavior` interface).

### Architectural Thinking Process

**As an architect, I see this problem:**

"Behaviors (fly, quack) vary across duck types, but they're tangled up in the inheritance tree. Every new behavior variant forces me to modify existing code. This violates Open/Closed Principle."

**This violates principles because:**

- Inheritance couples Duck subclasses to specific behaviors
- Can't reuse behaviors across different ducks easily
- Runtime flexibility is impossible

**If we introduce the Strategy pattern, we gain:**

- **Flexibility:** Swap behaviors at runtime
- **Reusability:** Share strategies across multiple ducks
- **Maintainability:** Add new behaviors without touching Duck
- **Testability:** Test strategies independently

**The trade-off is:**

- More classes (one per strategy)
- Slight indirection (delegation vs direct call)
- Worth it when behaviors vary frequently or need runtime changes

---

## The Benefits - What You Gain ✅

### Flexibility: What Becomes Easy to Change?

1. **Add New Behaviors** - No Duck Code Changes

   ```cpp
   // New requirement: supersonic flight
   class FlySuperSonic : public FlyBehavior {
       void fly() const override {
           std::cout << "Supersonic flight!\n";
       }
   };

   // Use it:
   duck->setFlyBehavior(std::make_unique<FlySuperSonic>());
   // No changes to Duck class!
   ```

2. **Runtime Behavior Changes**

   ```cpp
   Duck* model = new ModelDuck();
   model->performFly();  // "I can't fly"

   // Mid-simulation: attach rocket!
   model->setFlyBehavior(std::make_unique<FlyRocketPowered>());
   model->performFly();  // "I'm flying with a rocket!"
   ```

3. **Behavior Reuse Across Types**

   ```cpp
   MallardDuck mallard;     // Uses FlyWithWings
   RedheadDuck redhead;     // Also uses FlyWithWings
   // Same strategy object, no duplication!
   ```

### Maintainability: Easier to Understand/Debug

- **Single Responsibility:** Each class has ONE job
  - `Duck` = manage duck-specific state
  - `FlyBehavior` = encapsulate flying logic
- **Localized Changes:** Bug in rocket flight? Fix `FlyRocketPowered`, nowhere else
- **Clear Structure:** Behaviors are explicit, not buried in subclass overrides

### Testability: Isolated Testing

```cpp
// Test flying logic WITHOUT creating a duck!
TEST(FlyBehaviorTest, RocketPoweredFlight) {
    auto fly = std::make_unique<FlyRocketPowered>();
    fly->fly();  // Test in isolation
}

// Mock strategies for testing Duck:
class MockFlyBehavior : public FlyBehavior {
    void fly() const override { /* track calls */ }
};

Duck* duck = new MallardDuck();
duck->setFlyBehavior(std::make_unique<MockFlyBehavior>());
duck->performFly();  // Verify delegation works
```

---

## The Trade-offs - Be Honest ⚖️

### Added Complexity

**More Classes:**

- Before: 1 `Duck` base + 3 subclasses = 4 classes
- After: 1 `Duck` + 2 behavior interfaces + 6 strategy implementations = 9 classes

**More Indirection:**

- Before: Direct method call `duck.fly()`
- After: Delegation `duck.performFly()` → `flyBehavior->fly()`

### Performance Considerations

- **Virtual function calls:** Strategy methods are virtual (slight overhead)
- **Memory:** Extra pointers for behavior objects
- **Cache locality:** Behavior objects might not be co-located with Duck

**Mitigation:**

- Modern CPUs handle virtual calls efficiently (branch prediction)
- Memory overhead is negligible (2 pointers per duck)
- Performance impact is **insignificant** for most applications

### When Might This Be Overkill?

**DON'T use Strategy when:**

1. **Behaviors never change**
   - If all ducks always quack the same way, just use a simple method
   - Example: `swim()` is the same for all ducks → no strategy needed

2. **Only one or two variants**
   - If you only have "fly" and "don't fly", a boolean flag might suffice
   - Strategy shines with **multiple** behavior variants (3+)

3. **No runtime changes needed**
   - If behavior is determined at construction and never changes
   - But even then, Strategy improves testability and extensibility

4. **Performance-critical tight loops**
   - Game engines rendering 10,000 entities/frame
   - Virtual call overhead might matter (profile first!)

### When You SHOULD Use This

✅ Behaviors have multiple variants (3+ implementations)
✅ Need to switch behaviors at runtime
✅ Behaviors might change frequently (new requirements)
✅ Want to test behaviors independently
✅ Different objects need different combinations of behaviors

---

## Implementation Details

### Class Structure

```bash
FlyBehavior (interface)
├── FlyWithWings
├── FlyNoWay
└── FlyRocketPowered

QuackBehavior (interface)
├── Quack
├── Squeak
└── MuteQuack

Duck (abstract)
├── MallardDuck
└── ModelDuck
```

### Key Components

1. **Strategy Interfaces:** `FlyBehavior`, `QuackBehavior`
2. **Concrete Strategies:** Implement specific behaviors
3. **Context:** `Duck` class delegates to strategies
4. **Clients:** Create ducks and set behaviors

---

## Key Takeaways

### For a Software Architect

1. **Composition > Inheritance**
   - Inheritance = compile-time binding, rigid
   - Composition = runtime binding, flexible

2. **Encapsulate Variability**
   - Identify what changes (behaviors)
   - Isolate it from what stays the same (Duck structure)

3. **Program to Interfaces**
   - Duck depends on `FlyBehavior`, not `FlyWithWings`
   - Decouples client from implementations

4. **Open/Closed Principle**
   - Open for extension (new strategies)
   - Closed for modification (Duck unchanged)

### When to Apply

- Multiple behavior variants
- Runtime behavior changes needed
- Behaviors used by multiple classes
- High testability requirements
- Frequent behavior additions expected

### Anti-Patterns to Avoid

- ❌ Using Strategy for single behavior variant (overkill)
- ❌ Making strategies stateful (prefer stateless when possible)
- ❌ Forgetting virtual destructor in C++
- ❌ Not using smart pointers (memory leaks)

---

## Comparison to Related Patterns

### Strategy vs State

- **Strategy:** Client chooses which algorithm to use
- **State:** Object changes behavior based on internal state
- Both use composition, but intent differs

### Strategy vs Template Method

- **Strategy:** Behavior in separate classes (composition)
- **Template Method:** Behavior in subclasses (inheritance)
- Strategy = runtime flexibility, Template = compile-time

### Strategy vs Dependency Injection

- DI is a **technique** to provide strategies
- Strategy is the **pattern** that defines interchangeable behaviors
- Often used together

---

## Conclusion

The Strategy Pattern is your architectural answer to "How do I make behaviors flexible and reusable?"

**Core Insight:** Replace inheritance with composition to achieve runtime flexibility and maintainability.

**Remember:** Use this pattern when behaviors vary, not when everything is static. The added complexity pays off with flexibility and testability.

**Next Steps:** Look at the C++ implementation to see these principles in action with modern C++20 features!
