# Decorator Pattern - Starbuzz Coffee

## Overview

Demonstration of the **Decorator Pattern** using a coffee ordering system. Shows how to add responsibilities to objects dynamically by wrapping them with decorator objects, avoiding class explosion from feature combinations.

## Key Concepts

- **Open/Closed Principle:** Add new features (condiments) without modifying existing classes
- **Single Responsibility:** Each decorator handles ONE responsibility (e.g., Mocha adds mocha)
- **Composition over Inheritance:** Decorators wrap components via composition, not inheritance
- **IS-A and HAS-A:** Decorators ARE-A component (same interface) AND HAS-A component (wraps one)
- **Runtime Flexibility:** Wrap objects dynamically at runtime in any combination

## Project Structure

```text
03_starbuzz_coffee/
├── CMakeLists.txt          # Build configuration
├── main.cpp                # Main program entry point
├── inc/                    # Header files
│   ├── Beverage.h          # Abstract component
│   ├── CondimentDecorator.h # Abstract decorator
│   ├── Espresso.h          # Concrete component
│   ├── HouseBlend.h        # Concrete component
│   ├── DarkRoast.h         # Concrete component
│   ├── Decaf.h             # Concrete component
│   ├── Mocha.h             # Concrete decorator
│   ├── Whip.h              # Concrete decorator
│   └── Soy.h               # Concrete decorator
├── src/                    # Source files (empty for header-only implementation)
├── out/
│   └── build/              # Build output directory
├── scripts/                # Build and run scripts
│   ├── conf.sh            # Configure CMake
│   ├── build.sh           # Build project
│   ├── run.sh             # Run executable
│   └── all.sh             # Run all steps (configure + build + run)
├── UML/                    # UML diagrams
│   └── diagram.puml
├── Decorator_Pattern.md     # Comprehensive pattern analysis
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
./starbuzz_coffee
```

## Expected Output

```text
=== Starbuzz Coffee Ordering System ===

--- Order 1 ---
Espresso $1.99

--- Order 2 ---
Dark Roast, Mocha, Mocha, Whip $1.49

--- Order 3 ---
House Blend Coffee, Soy, Mocha, Whip $1.34

--- Order 4 ---
Decaf, Whip $1.15

=== Demonstration Complete ===
```

## Files

### Component Hierarchy (in `inc/`)

**Abstract Component:**

- `Beverage.h` - Base class for all beverages

**Concrete Components:**

- `Espresso.h` - Espresso beverage ($1.99)
- `HouseBlend.h` - House blend coffee ($0.89)
- `DarkRoast.h` - Dark roast coffee ($0.99)
- `Decaf.h` - Decaf coffee ($1.05)

### Decorator Hierarchy (in `inc/`)

**Abstract Decorator:**

- `CondimentDecorator.h` - Base class for all condiment decorators

**Concrete Decorators:**

- `Mocha.h` - Adds mocha (+$0.20)
- `Whip.h` - Adds whipped cream (+$0.10)
- `Soy.h` - Adds soy milk (+$0.15)

### Client

- `main.cpp` - Demonstration program showing beverage decoration

## Design Highlights

### Modern C++ Features Used

- **Smart Pointers** (`std::unique_ptr`) - Automatic memory management for wrapped objects
- **Move Semantics** - Efficient transfer of ownership when wrapping
- **RAII** - Automatic cleanup of decorator chains
- **Const Correctness** - Methods marked `const` where appropriate
- **Virtual Destructors** - Proper cleanup in polymorphic hierarchies
- **Explicit Constructors** - Prevent implicit conversions

### Why `std::unique_ptr`?

Decorators **exclusively own** the objects they wrap:

- No sharing needed → no reference counting overhead
- Clear ownership semantics
- Automatic cleanup of entire chain
- Move semantics = zero-copy wrapping

### Decorator Chain Example

```cpp
// Start with base component
std::unique_ptr<Beverage> b = std::make_unique<Espresso>();  // $1.99

// Wrap with decorators (ownership transferred via move)
b = std::make_unique<Mocha>(std::move(b));  // $1.99 + $0.20
b = std::make_unique<Mocha>(std::move(b));  // $2.19 + $0.20 (double mocha!)
b = std::make_unique<Whip>(std::move(b));   // $2.39 + $0.10

// Result: "Espresso, Mocha, Mocha, Whip" - $2.49
```

**How cost() works:**

1. `b->cost()` calls `Whip::cost()`
2. `Whip::cost()` returns `0.10 + wrappedBeverage->cost()`
3. Calls second `Mocha::cost()` → `0.20 + wrappedBeverage->cost()`
4. Calls first `Mocha::cost()` → `0.20 + wrappedBeverage->cost()`
5. Calls `Espresso::cost()` → `1.99`
6. **Total: 1.99 + 0.20 + 0.20 + 0.10 = 2.49**

## Pattern Benefits Demonstrated

1. **Avoid Class Explosion:** Don't need `EspressoWithMochaAndWhip`, `EspressoWithSoy`, etc. (would be 64+ classes!)
2. **Open/Closed Principle:** Add new condiments without modifying Beverage or existing decorators
3. **Runtime Flexibility:** Wrap in any order, any combination, at runtime
4. **Multiple Quantities:** Want double mocha? Wrap twice!
5. **Single Responsibility:** Each decorator handles ONE condiment

## Architecture

```text
Beverage (Abstract Component)
├── getDescription() : string
└── cost() : double

ConcreteComponents (Espresso, HouseBlend, DarkRoast, Decaf)
├── extend Beverage
└── implement cost()

CondimentDecorator (Abstract Decorator)
├── extends Beverage (IS-A)
├── HAS-A unique_ptr<Beverage> (wraps component)
└── getDescription() : string (abstract)

ConcreteDecorators (Mocha, Whip, Soy)
├── extend CondimentDecorator
├── wrap a Beverage
└── cost() { return condimentCost + wrappedBeverage->cost(); }
```

## Key Decorator Pattern Principles

1. **Decorators have the same type as wrapped objects** - Enables transparent wrapping
2. **Decorators wrap components via composition** - Not inheritance
3. **Decorators delegate to wrapped objects** - Add behavior before/after delegation
4. **Can wrap unlimited times** - Recursive structure
5. **Open for extension, closed for modification** - Add features without changing existing code

## Comparison: Before vs After

| Aspect | Inheritance/Flags (Before) | Decorator Pattern (After) |
|--------|----------------------------|---------------------------|
| **Adding Feature** | Modify base class or create EspressoWithMocha subclass | Create Mocha decorator, wrap Espresso |
| **Combinations** | 64+ classes for 4 beverages × 4 condiments | 8 classes total (4 beverages + 4 decorators) |
| **Multiple Quantities** | Need `hasDoubleMocha` flag | Wrap twice: `new Mocha(new Mocha(espresso))` |
| **Flexibility** | Compile-time only | Runtime wrapping in any combination |
| **Maintenance** | Every new condiment touches base class | Add decorator, existing code unchanged |

## Further Reading

See [Decorator_Pattern.md](Decorator_Pattern.md) for detailed architectural analysis, including:

- Problem analysis (class explosion, inflexible flags)
- Real-world embedded systems example (device drivers)
- Design principles explained (Open/Closed, composition over inheritance)
- Trade-offs and when to use (avoid class explosion, runtime flexibility)
- C++ specific considerations (smart pointers, move semantics, virtual destructors)
