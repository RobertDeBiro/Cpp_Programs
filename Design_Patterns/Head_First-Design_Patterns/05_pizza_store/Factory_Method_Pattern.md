# Factory Method Pattern - Comprehensive Analysis

## Pattern Overview

**Factory Method Pattern** defines an interface for creating objects, but lets subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.

**Key Intent:** Encapsulate object creation so that the client code depends on abstractions (interfaces) rather than concrete implementations.

**Also Known As:** Virtual Constructor

---

## The Problem: Tight Coupling and Dependency Issues

### Bad Architecture Example: Hardcoded Pizza Creation

```cpp
// BAD: Direct instantiation creates tight coupling
class PizzaStore {
public:
    Pizza* orderPizza(const std::string& type) {
        Pizza* pizza = nullptr;

        // PROBLEM 1: Tight coupling to concrete classes
        if (type == "cheese") {
            pizza = new NYStyleCheesePizza();  // Direct dependency!
        } else if (type == "pepperoni") {
            pizza = new NYStylePepperoniPizza();
        }

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        return pizza;
    }
};
```

### Pain Points

1. **Violates Dependency Inversion Principle**
   - High-level module (`PizzaStore`) depends on low-level modules (concrete Pizza classes)
   - Should depend on abstractions instead

2. **Violates Open/Closed Principle**
   - Adding new pizza types requires modifying `PizzaStore` class
   - Cannot extend without modification

3. **Regional Variations Explosion**
   - What if you need Chicago-style pizzas? California-style?
   - Copy-paste entire `orderPizza()` method with different concrete classes?
   - Code duplication nightmare

4. **No Centralized Control**
   - Pizza creation logic scattered across codebase
   - Difficult to ensure consistency in how pizzas are created

5. **Testing Nightmare**
   - Cannot easily mock or substitute pizza implementations
   - Unit testing `PizzaStore` requires instantiating real Pizza objects

### Example of Cascading Problems

```cpp
// As business grows, this becomes unmaintainable:
Pizza* orderPizza(const std::string& type, const std::string& region) {
    Pizza* pizza = nullptr;

    if (region == "NY") {
        if (type == "cheese") pizza = new NYStyleCheesePizza();
        else if (type == "pepperoni") pizza = new NYStylePepperoniPizza();
        else if (type == "veggie") pizza = new NYStyleVeggiePizza();
        // ... 10 more types
    } else if (region == "Chicago") {
        if (type == "cheese") pizza = new ChicagoStyleCheesePizza();
        else if (type == "pepperoni") pizza = new ChicagoStylePepperoniPizza();
        // ... 10 more types
    } else if (region == "California") {
        // ... another 10 types
    }
    // This grows exponentially! 3 regions × 10 types = 30 if-else branches!
}
```

**Result:** A single method with 50+ lines of if-else logic, violating Single Responsibility Principle and making code impossible to maintain.

### UML Diagram: Bad Design

See `UML/Bad_Hardcoded_Creation.puml` for the class diagram showing the tightly-coupled approach with hardcoded pizza creation (red-highlighted problem class).

---

## Design Principles

### 1. Dependency Inversion Principle (DIP)

**Definition:** High-level modules should not depend on low-level modules. Both should depend on abstractions.

**Before Factory Method:**

```text
PizzaStore (high-level)
    ↓ depends on
NYStyleCheesePizza (low-level concrete class)
ChicagoStyleCheesePizza (low-level concrete class)
```

**After Factory Method:**

```text
PizzaStore (high-level)
    ↓ depends on
Pizza (abstraction)
    ↑ implemented by
NYStyleCheesePizza, ChicagoStyleCheesePizza (low-level)
```

**Key Insight:** By introducing the `Pizza` interface and deferring creation to subclasses, `PizzaStore` no longer knows about concrete pizza types. **Dependency arrows now point UPWARD** toward abstractions.

### 2. Open/Closed Principle

**Definition:** Classes should be open for extension but closed for modification.

- **Open for Extension:** Create new `PizzaStore` subclasses for new regions (e.g., `CaliforniaPizzaStore`)
- **Closed for Modification:** Never need to change existing `PizzaStore`, `NYPizzaStore`, or `ChicagoPizzaStore` classes

### 3. Single Responsibility Principle

- `PizzaStore`: Responsible for the **pizza ordering workflow** (prepare, bake, cut, box)
- `NYPizzaStore`/`ChicagoPizzaStore`: Responsible for **deciding which pizza to create** (creation logic)
- `Pizza` subclasses: Responsible for **pizza-specific details** (ingredients, cutting style)

Each class has ONE reason to change.

### 4. Program to an Interface, Not an Implementation

```cpp
// Good: Depend on abstraction
Pizza* pizza = createPizza(type);  // Returns Pizza*, not NYStyleCheesePizza*

// Bad: Depend on concrete class
NYStyleCheesePizza* pizza = new NYStyleCheesePizza();
```

---

## The Solution: Factory Method Pattern

### Structure

```text
┌─────────────────────┐
│   PizzaStore        │  ← Abstract Creator (High-level)
├─────────────────────┤
│ + orderPizza()      │  ← Template method (invariant algorithm)
│ # createPizza() = 0 │  ← Factory method (varying step)
└─────────────────────┘
         △
         │ extends
    ┌────┴────┐
    │         │
┌───┴───────┐ ┌────────────────┐
│NYPizzaStore│ │ChicagoPizzaStore│  ← Concrete Creators
├───────────┤ ├────────────────┤
│createPizza│ │createPizza     │  ← Override to instantiate
└───────────┘ └────────────────┘      concrete products
    │              │
    │ creates      │ creates
    ↓              ↓
┌────────────┐ ┌─────────────────────┐
│NYStyle     │ │ChicagoStyle         │  ← Concrete Products
│CheesePizza │ │CheesePizza          │
└────────────┘ └─────────────────────┘
```

### Key Components

1. **Product Interface** (`Pizza`)
   - Defines interface for objects created by factory method
   - Example: `prepare()`, `bake()`, `cut()`, `box()`

2. **Concrete Products** (`NYStyleCheesePizza`, `ChicagoStyleCheesePizza`)
   - Implement the Product interface
   - Represent different variants of products

3. **Creator** (`PizzaStore`)
   - Declares factory method `createPizza()` that returns Product
   - Contains template method `orderPizza()` that calls factory method
   - **Depends only on Product interface, NOT concrete products**

4. **Concrete Creators** (`NYPizzaStore`, `ChicagoPizzaStore`)
   - Override factory method to instantiate specific Concrete Products
   - Encapsulate knowledge of which product variant to create

### How It Works

```cpp
// Client code
PizzaStore* nyStore = new NYPizzaStore();
Pizza* pizza = nyStore->orderPizza("cheese");
//                      ^^^^^^^^^^^
//                      Calls template method in PizzaStore
//                           ↓
//                      Calls createPizza("cheese")
//                           ↓
//                      Dispatched to NYPizzaStore::createPizza()
//                           ↓
//                      Returns new NYStyleCheesePizza()
//                           ↓
//                      PizzaStore::orderPizza() continues with
//                      pizza->prepare(), pizza->bake(), etc.
```

**Critical Insight:** The high-level `PizzaStore::orderPizza()` method orchestrates the workflow WITHOUT knowing which concrete pizza class is being used. **Polymorphism handles dispatch at runtime.**

---

## Benefits and Trade-offs

### Benefits

1. **Eliminates Tight Coupling**
   - High-level code depends only on abstractions
   - Concrete product classes can change without affecting creators

2. **Single Point of Product Creation**
   - Each creator encapsulates knowledge of which products to create
   - Centralized control over object instantiation

3. **Extensibility Without Modification**
   - Add new product variants: Create new Concrete Product classes
   - Add new creator variants: Create new Concrete Creator classes
   - Existing code remains unchanged (Open/Closed Principle)

4. **Parallel Class Hierarchies**
   - Product hierarchy: `Pizza` → `NYStyleCheesePizza`, `ChicagoStyleCheesePizza`
   - Creator hierarchy: `PizzaStore` → `NYPizzaStore`, `ChicagoPizzaStore`
   - Both hierarchies evolve independently

5. **Testing and Mocking**
   - Can create test doubles by implementing Product interface
   - Can test template method algorithm independently of product creation

### Trade-offs

1. **Increased Number of Classes**
   - Each product variant needs a class
   - Each creator variant needs a class
   - Mitigated by: Clear separation of concerns and maintainability gains

2. **Indirection**
   - Object creation is less obvious than `new ConcreteClass()`
   - Mitigated by: Clear naming (e.g., `createPizza()`) and documentation

3. **Requires Planning**
   - Must identify common product interface upfront
   - Mitigated by: Refactoring is easier than managing conditional creation logic

4. **Not Always Necessary**
   - Overkill for simple applications with no variation
   - Use when: You anticipate multiple product variants OR need to defer creation

### When to Use Factory Method

- ✅ Class cannot anticipate which objects it needs to create
- ✅ Subclasses should specify which objects to create
- ✅ You want to localize knowledge of which concrete class to instantiate
- ✅ You have parallel class hierarchies
- ❌ You only have one product type with no variants (use direct instantiation)
- ❌ Creation logic is trivial and unlikely to change (YAGNI principle)

---

## Pattern Relationships

### Factory Method vs Other Patterns

1. **Factory Method + Template Method**
   - `orderPizza()` is a Template Method that calls Factory Method `createPizza()`
   - Template Method defines skeleton, Factory Method provides varying step

2. **Factory Method → Abstract Factory**
   - Factory Method creates ONE product
   - Abstract Factory creates FAMILIES of related products
   - Example: `PizzaIngredientFactory` creates {Dough, Sauce, Cheese} as a family

3. **Factory Method + Strategy**
   - Both use composition over inheritance
   - Strategy: Varies algorithm/behavior dynamically
   - Factory Method: Varies object creation statically (subclass decides)

4. **Factory Method → Singleton**
   - Factory can return Singleton instances
   - Example: `createPizza("cheese")` could return same instance if pizzas were immutable

5. **Factory Method + Prototype**
   - Prototype: Clone existing object instead of creating from scratch
   - Factory Method with Prototype: `createPizza()` clones a prototype instead of using `new`

### Common Combinations in Network Systems Example

```cpp
// Factory Method creates protocol handlers
class ProtocolHandlerFactory {
protected:
    virtual std::unique_ptr<ProtocolHandler> createHandler(const std::string& protocol) = 0;
};

// Abstract Factory creates families of related objects
class NetworkStackFactory {
public:
    virtual std::unique_ptr<ProtocolHandler> createHandler() = 0;
    virtual std::unique_ptr<Authenticator> createAuthenticator() = 0;
    virtual std::unique_ptr<Serializer> createSerializer() = 0;
};

// Strategy for different authentication mechanisms
class Authenticator {
public:
    virtual bool authenticate(const Credentials& creds) = 0;
};

// Observer for connection state changes
class ConnectionObserver {
public:
    virtual void onConnectionEstablished(Connection* conn) = 0;
    virtual void onConnectionClosed(Connection* conn) = 0;
};
```

---

## Summary: The Power of Factory Method

**Before Factory Method:**

- High-level code tightly coupled to concrete classes
- Cannot extend without modifying existing code
- Testing requires instantiating real dependencies
- Regional/variant-specific logic scattered everywhere

**After Factory Method:**

- ✅ **Dependency Inversion:** High-level depends only on abstractions
- ✅ **Open/Closed Principle:** Extend by creating new subclasses
- ✅ **Single Responsibility:** Creation logic isolated in factory methods
- ✅ **Testability:** Can inject mock products via subclass
- ✅ **Flexibility:** Runtime polymorphism handles dispatching
- ✅ **Maintainability:** Parallel hierarchies evolve independently

**Architectural Thinking:**

> When you find yourself writing `if (type == "A") return new ConcreteA()` repeatedly, you have a code smell. Factory Method transforms this into a design where **subclasses decide what to instantiate**, letting you extend behavior without modifying existing code. This is the essence of **programming to abstractions** and **dependency inversion**.

---

## References

- **Design Principles:** SOLID principles (Single Responsibility, Open/Closed, Dependency Inversion)
- **C++ Features:** Smart pointers (`unique_ptr`), RAII, move semantics, virtual destructors
- **Related Patterns:** Template Method, Abstract Factory, Strategy, Prototype
- **Real-World Application:** Network protocol handlers, device drivers, plugin systems

