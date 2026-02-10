# Factory Method Pattern - Pizza Store

## Overview

Demonstration of the **Factory Method Pattern** using a pizza store ordering system. Shows how to defer object instantiation to subclasses, allowing high-level code to depend on abstractions rather than concrete implementations.

## Key Concepts

- **Dependency Inversion Principle:** High-level modules depend on abstractions, not concrete classes
- **Open/Closed Principle:** Add new store types without modifying existing code
- **Factory Method:** Subclasses decide which concrete product to instantiate
- **Template Method:** `orderPizza()` defines invariant workflow, `createPizza()` is the hook
- **Parallel Hierarchies:** Creator hierarchy (stores) and Product hierarchy (pizzas) evolve independently

## Project Structure

```text
05_pizza_store/
├── CMakeLists.txt              # Build configuration
├── main.cpp                    # Main program entry point
├── inc/                        # Header files
│   ├── Pizza.h                 # Abstract product
│   ├── NYStyleCheesePizza.h    # Concrete product (NY cheese)
│   ├── NYStylePepperoniPizza.h # Concrete product (NY pepperoni)
│   ├── ChicagoStyleCheesePizza.h    # Concrete product (Chicago cheese)
│   ├── ChicagoStylePepperoniPizza.h # Concrete product (Chicago pepperoni)
│   ├── PizzaStore.h            # Abstract creator
│   ├── NYPizzaStore.h          # Concrete creator (NY)
│   └── ChicagoPizzaStore.h     # Concrete creator (Chicago)
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
├── Factory_Method_Pattern.md         # Comprehensive pattern analysis
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
./pizza_store
```

## Expected Output

```text
=== Pizza Store Factory Method Demonstration ===

--- Ethan's Order (NY Store) ---
Preparing NY Style Sauce and Cheese Pizza
Tossing dough...
Adding sauce...
Adding toppings:
   Grated Reggiano Cheese
Bake for 25 minutes at 350
Cutting the pizza into diagonal slices
Place pizza in official PizzaStore box
Ethan ordered a NY Style Sauce and Cheese Pizza

--- Joel's Order (Chicago Store) ---
Preparing Chicago Style Deep Dish Cheese Pizza
Tossing dough...
Adding sauce...
Adding toppings:
   Shredded Mozzarella Cheese
Bake for 25 minutes at 350
Cutting the pizza into square slices
Place pizza in official PizzaStore box
Joel ordered a Chicago Style Deep Dish Cheese Pizza

[... more orders ...]

=== Demonstration Complete ===

Key Observations:
1. orderPizza() workflow is identical for all stores (Template Method)
2. Each store creates its region-specific pizzas (Factory Method)
3. Chicago pizzas use square cuts, NY pizzas use diagonal cuts
4. Main() depends only on abstract PizzaStore and Pizza interfaces
5. Adding California store wouldn't modify existing code (Open/Closed)
```

## Files

### Creator Hierarchy (in `inc/`)

**Abstract Creator:**

- `PizzaStore.h` - Declares factory method `createPizza()`, implements template method `orderPizza()`

**Concrete Creators:**

- `NYPizzaStore.h` - Creates NY-style pizzas (thin crust, marinara sauce)
- `ChicagoPizzaStore.h` - Creates Chicago-style pizzas (deep dish, plum tomato sauce)

### Product Hierarchy (in `inc/`)

**Abstract Product:**

- `Pizza.h` - Defines interface for all pizzas (prepare, bake, cut, box)

**Concrete Products (NY Style):**

- `NYStyleCheesePizza.h` - Thin crust, marinara sauce, Reggiano cheese
- `NYStylePepperoniPizza.h` - NY cheese pizza with pepperoni and vegetables

**Concrete Products (Chicago Style):**

- `ChicagoStyleCheesePizza.h` - Deep dish, plum tomato sauce, mozzarella cheese, square cut
- `ChicagoStylePepperoniPizza.h` - Chicago cheese pizza with pepperoni and vegetables, square cut

### Client

- `main.cpp` - Demonstration program showing polymorphic pizza ordering

## Design Highlights

### Modern C++ Features Used

- **Smart Pointers** (`std::unique_ptr`) - Automatic memory management, clear ownership semantics
- **Move Semantics** - Efficient transfer of ownership when returning pizzas
- **RAII** - Automatic cleanup of pizza objects
- **Virtual Destructors** - Proper cleanup in polymorphic hierarchies
- **Pure Virtual Functions** - Force subclass implementation of factory method
- **Const Correctness** - Methods marked `const` where appropriate
- **Explicit Constructors** - Prevent implicit conversions
- **Deleted Copy Operations** - Pizzas are unique products, not copyable

### Why `std::unique_ptr`?

Pizza stores **exclusively own** the pizzas they create:

- No sharing needed → no reference counting overhead
- Clear ownership semantics (caller takes ownership after `orderPizza()`)
- Automatic cleanup
- Move semantics = zero-copy return

### Factory Method in Action

```cpp
// Client code depends only on abstractions
std::unique_ptr<PizzaStore> store = std::make_unique<NYPizzaStore>();
auto pizza = store->orderPizza("cheese");
//                   ^^^^^^^^^^^
//                   Calls PizzaStore::orderPizza()
//                        ↓
//                   Calls createPizza("cheese")
//                        ↓
//                   Polymorphic dispatch to NYPizzaStore::createPizza()
//                        ↓
//                   Returns new NYStyleCheesePizza()
//                        ↓
//                   PizzaStore::orderPizza() continues with prepare, bake, cut, box
```

**How it works:**

1. `orderPizza()` is a **template method** (invariant algorithm)
2. `createPizza()` is the **factory method** (varying step)
3. Subclasses override `createPizza()` to instantiate region-specific pizzas
4. High-level `orderPizza()` never knows about concrete pizza classes

## Pattern Benefits Demonstrated

1. **Dependency Inversion:** High-level code depends on `Pizza` interface, not concrete classes
2. **Open/Closed Principle:** Add `CaliforniaPizzaStore` without modifying existing code
3. **Single Responsibility:** Store handles ordering workflow, factory method handles creation
4. **Encapsulation:** Each store encapsulates knowledge of which pizzas to create
5. **Testability:** Can mock `Pizza` interface for testing `orderPizza()` logic

## Architecture

```text
PizzaStore (Abstract Creator)
├── orderPizza(type) : unique_ptr<Pizza>  ← Template method (public)
└── createPizza(type) : unique_ptr<Pizza> ← Factory method (protected, pure virtual)

Concrete Creators (NYPizzaStore, ChicagoPizzaStore)
├── Override createPizza() to instantiate region-specific pizzas
└── Inherit orderPizza() template method unchanged

Pizza (Abstract Product)
├── prepare(), bake(), cut(), box()
└── getName()

Concrete Products (NYStyleCheesePizza, ChicagoStyleCheesePizza, etc.)
├── Implement product-specific details (ingredients, cutting style)
└── Inherit common operations from Pizza
```

## Key Factory Method Principles

1. **Subclasses decide what to instantiate** - Factory method defers creation to subclasses
2. **Program to interfaces** - High-level code depends on abstractions (`Pizza`, `PizzaStore`)
3. **Encapsulate creation** - Creation logic isolated in factory method
4. **Parallel hierarchies** - Creator and Product hierarchies vary independently
5. **Template Method + Factory Method** - Combine patterns for powerful extensibility

## Comparison: Before vs After

| Aspect | Hardcoded Creation (Before) | Factory Method (After) |
|--------|----------------------------|------------------------|
| **Adding Region** | Duplicate orderPizza() with new if-else branches | Create new concrete creator subclass |
| **Coupling** | High-level depends on concrete pizza classes | High-level depends only on abstractions |
| **Extensibility** | Modify existing code (violates Open/Closed) | Extend via subclassing (Open/Closed) |
| **Testing** | Must instantiate real pizzas | Can mock Pizza interface |
| **Maintenance** | Changes ripple through codebase | Changes localized to factory methods |

## Real-World Applications

### Network Protocol Handler Factory (See Factory_Method_Pattern.md)

```cpp
// Abstract Creator
class ProtocolHandlerFactory {
protected:
    virtual std::unique_ptr<ProtocolHandler> createHandler(const std::string& protocol) = 0;
};

// Concrete Creators for different deployment regions
class EuropeanGateway : public ProtocolHandlerFactory {
protected:
    std::unique_ptr<ProtocolHandler> createHandler(const std::string& protocol) override {
        if (protocol == "http") return std::make_unique<HttpHandler>();
        if (protocol == "mqtt") return std::make_unique<MqttHandler>();
        if (protocol == "amqp") return std::make_unique<AmqpHandler>();
        return nullptr;
    }
};

class AsianGateway : public ProtocolHandlerFactory {
protected:
    std::unique_ptr<ProtocolHandler> createHandler(const std::string& protocol) override {
        if (protocol == "http") return std::make_unique<HttpHandler>();
        if (protocol == "coap") return std::make_unique<CoapHandler>();
        if (protocol == "proprietary") return std::make_unique<ProprietaryHandler>();
        return nullptr;
    }
};
```

**Benefits:**

- European and Asian deployments can have different protocol stacks
- Gateway logic (authentication, routing, logging) is shared
- Protocol teams work independently
- Can test gateway logic without real network handlers

## Further Reading

See [Factory_Method_Pattern.md](Factory_Method_Pattern.md) for detailed architectural analysis, including:

- Problem analysis (tight coupling, dependency issues)
- Real-world network systems example (protocol handler factory)
- Design principles explained (Dependency Inversion, Open/Closed, Single Responsibility)
- Benefits, trade-offs, and when to use Factory Method
- C++ specific considerations (smart pointers, virtual destructors, move semantics)
- Pattern relationships (Template Method, Abstract Factory, Strategy, Prototype)
