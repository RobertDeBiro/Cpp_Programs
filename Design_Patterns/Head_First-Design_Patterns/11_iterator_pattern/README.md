# Iterator and Composite Patterns

## Overview

This project demonstrates two fundamental behavioral and structural patterns from the "Head First Design Patterns" book:

1. **Iterator Pattern** (Behavioral) - Provides sequential access to collection elements without exposing underlying representation
2. **Composite Pattern** (Structural) - Composes objects into tree structures to represent part-whole hierarchies

Both patterns work together to create flexible, maintainable code that separates concerns and promotes uniform treatment of objects.

## Pattern Descriptions

### Iterator Pattern

**Intent:** Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.

**Problem it Solves:**
- Different collections use different internal representations (arrays, vectors, maps)
- Client code depends on specific collection types
- Changing collection implementation breaks client code
- Traversal logic mixed with business logic

**Solution:**
- Define an Iterator interface with `hasNext()` and `next()` methods
- Each collection provides its own iterator implementation
- Client code works with the Iterator interface, not specific collections
- Separates traversal responsibility from collection management

**Key Benefit:** You can change the collection's internal representation without affecting clients.

### Composite Pattern

**Intent:** Compose objects into tree structures to represent part-whole hierarchies. Let clients treat individual objects and compositions uniformly.

**Problem it Solves:**
- Need to represent hierarchical structures (trees)
- Client code must distinguish between leaf objects and containers
- Operations on trees require complex traversal logic
- Cannot nest objects arbitrarily

**Solution:**
- Define a Component interface for both leaves and composites
- Leaf objects implement Component (e.g., MenuItem)
- Composite objects implement Component and contain children (e.g., Menu)
- Operations are recursive - composites delegate to their children
- Client treats leaves and composites uniformly through Component interface

**Key Benefit:** You can build complex tree structures and treat individual objects and compositions the same way.

## Project Structure

```
11_iterator_pattern/
├── CMakeLists.txt              # Build configuration
├── main.cpp                    # Demonstration of both patterns
├── inc/                        # Header files
│   ├── Iterator.h             # Iterator interface
│   ├── Menu.h                 # Collection interface
│   ├── MenuItem.h             # Menu item class (used in Iterator)
│   ├── PancakeHouseMenu.h     # Concrete collection (vector-based)
│   ├── DinerMenu.h            # Concrete collection (array-based)
│   ├── CafeMenu.h             # Concrete collection (map-based)
│   ├── Waitress.h             # Client using Iterator Pattern
│   ├── MenuComponent.h        # Component interface (Composite)
│   ├── CompositeMenuItem.h    # Leaf component
│   ├── CompositeMenu.h        # Composite component
│   └── CompositeWaitress.h    # Client using Composite Pattern
├── src/                       # Source files (empty for header-only)
├── out/build/                 # Build output directory
├── scripts/                   # Build and run scripts
│   ├── conf.sh               # Configure CMake
│   ├── build.sh              # Build project
│   ├── run.sh                # Run executable
│   └── all.sh                # Run all steps
├── UML/                       # PlantUML diagrams
│   ├── iterator_pattern.puml
│   └── composite_pattern.puml
├── Iterator_and_Composite_Pattern.md        # Comprehensive pattern analysis (800+ lines)
└── README.md                  # This file
```

## How the Patterns Work

### Iterator Pattern Example

```cpp
// Different menus with different internal collections
PancakeHouseMenu pancakeMenu;  // Uses std::vector internally
DinerMenu dinerMenu;           // Uses std::array internally
CafeMenu cafeMenu;             // Uses std::map internally

// Client doesn't know about internal representations
std::vector<Menu*> menus = {&pancakeMenu, &dinerMenu, &cafeMenu};
Waitress waitress(menus);

// Uniform access through Iterator interface
waitress.printMenu();  // Works for all menu types!
```

Each menu provides an iterator that knows how to traverse its specific collection type, but the client only works with the Iterator interface.

### Composite Pattern Example

```cpp
// Build hierarchical menu structure
auto allMenus = std::make_unique<CompositeMenu>("ALL MENUS", "All menus combined");

auto pancakeMenu = std::make_unique<CompositeMenu>("PANCAKE HOUSE MENU", "Breakfast");
pancakeMenu->add(std::make_unique<CompositeMenuItem>("Waffles", "With berries", true, 3.59));
pancakeMenu->add(std::make_unique<CompositeMenuItem>("Pancakes", "With eggs", false, 2.99));

auto dinerMenu = std::make_unique<CompositeMenu>("DINER MENU", "Lunch");
dinerMenu->add(std::make_unique<CompositeMenuItem>("BLT", "Bacon sandwich", false, 2.99));

// Nested menu - composite within composite!
auto dessertMenu = std::make_unique<CompositeMenu>("DESSERT MENU", "Desserts");
dessertMenu->add(std::make_unique<CompositeMenuItem>("Apple Pie", "With ice cream", true, 1.59));
dinerMenu->add(std::move(dessertMenu));  // Nest dessert menu in diner menu

// Build tree
allMenus->add(std::move(pancakeMenu));
allMenus->add(std::move(dinerMenu));

// Print entire hierarchy with one call - recursion handles everything!
allMenus->print();
```

The Composite Pattern allows us to build arbitrary tree structures and treat leaves (MenuItems) and composites (Menus) uniformly.

## Patterns Working Together

The Iterator and Composite Patterns complement each other:

- **Composite** provides the tree structure
- **Iterator** provides uniform traversal of that structure
- Together: Complex tree traversal hidden behind simple Iterator interface

Example: A CompositeIterator can use a stack to perform depth-first traversal of a Composite structure, hiding the complexity from clients.

## Design Principles Demonstrated

### 1. Single Responsibility Principle
- Collection manages storage
- Iterator manages traversal
- Each class has one reason to change

### 2. Open/Closed Principle
- Open for extension: Add new collection types without modifying clients
- Closed for modification: Existing code doesn't change

### 3. Dependency Inversion Principle
- Clients depend on Iterator interface, not concrete collections
- High-level modules don't depend on low-level modules

### 4. Programming to Interfaces
- Clients work with Iterator and Component interfaces
- Concrete implementations hidden

## Real-World Applications

### Iterator Pattern Applications
- **Embedded Systems**: Sensor array traversal, device register iteration
- **Network Systems**: Packet processing, connection pooling
- **File Systems**: Directory traversal, file iteration
- **Databases**: Result set iteration, cursor-based access

### Composite Pattern Applications
- **Embedded Systems**: Device hierarchy (System → Subsystems → Components)
- **File Systems**: Directory structure (folders contain files and folders)
- **GUI Systems**: Widget trees (containers contain widgets)
- **Graphics**: Scene graphs (groups contain shapes and other groups)

### Combined Application Example
**Embedded Device Management System:**
- Devices organized hierarchically (Composite)
- Iterate through all devices uniformly (Iterator)
- Initialize/shutdown entire subsystems recursively
- Monitor system status across hierarchy

## Building and Running

### Prerequisites
- C++20 compatible compiler (GCC 10+, Clang 10+, or MSVC 2019+)
- CMake 3.20 or higher
- Make build system

### Quick Start

Use the all-in-one script:
```bash
cd scripts
./all.sh
```

This script will:
1. Configure the project with CMake
2. Build the executable
3. Run the demonstration

### Manual Build Steps

**Configure:**
```bash
cd scripts
./conf.sh
```

**Build:**
```bash
./build.sh
```

**Run:**
```bash
./run.sh
```

### Expected Output

The program demonstrates both patterns:

1. **Iterator Pattern Section:**
   - Prints menus using different collection types (array, vector, map)
   - Shows uniform access through Iterator interface
   - Demonstrates vegetarian menu filtering

2. **Composite Pattern Section:**
   - Builds hierarchical menu structure
   - Shows nested menus (e.g., dessert menu within diner menu)
   - Demonstrates recursive printing of entire tree

3. **Pattern Comparison:**
   - Explains differences and similarities
   - Shows how they complement each other

## Key Implementation Details

### Iterator Pattern

**Key Classes:**
- `Iterator` - Interface with `hasNext()` and `next()`
- `Menu` - Aggregate interface with `createIterator()`
- `DinerMenuIterator`, `PancakeMenuIterator`, `CafeMenuIterator` - Concrete iterators
- `Waitress` - Client that uses iterators

**Design Decision:** Nested iterator classes
- Iterators are private nested classes within their collections
- Encapsulates iterator implementation details
- Iterator can access collection's private members

### Composite Pattern

**Key Classes:**
- `MenuComponent` - Component interface for both leaf and composite
- `CompositeMenuItem` - Leaf (individual menu item)
- `CompositeMenu` - Composite (contains menu items and/or other menus)
- `CompositeWaitress` - Client that treats leaf and composite uniformly

**Design Decision:** Transparency over Safety
- Both leaf and composite implement same interface
- Unsupported operations throw exceptions at runtime
- Trade-off: Simplicity vs compile-time safety

### Modern C++ Features Used

- **C++20 Standard**: Latest language features
- **Smart Pointers**: `std::unique_ptr` for ownership, raw pointers for borrowing
- **Move Semantics**: Efficient object transfer
- **`[[nodiscard]]` Attribute**: Encourage checking return values
- **Range-based For Loops**: Clean iteration syntax
- **Auto Type Deduction**: Simplify code

## Testing

The main.cpp file includes comprehensive demonstrations:

1. **Iterator Pattern Tests:**
   - Multiple collection types (array, vector, map)
   - Uniform access through Iterator
   - Filtering (vegetarian items)
   - Item lookups

2. **Composite Pattern Tests:**
   - Building tree structures
   - Nested composites (menu within menu)
   - Recursive operations (print)
   - Uniform treatment of leaf and composite

## When to Use These Patterns

### Use Iterator Pattern When:
- You need to access collection elements without exposing internal representation
- You want uniform access to different collection types
- You need to support multiple simultaneous traversals
- You want to separate traversal logic from collection

### Use Composite Pattern When:
- You need to represent part-whole hierarchies
- You want to treat individual objects and compositions uniformly
- Your structure is recursive (trees)
- You need operations on entire hierarchies

### Use Both Together When:
- You have hierarchical structures that need uniform traversal
- You want to hide tree traversal complexity
- You need flexible access to complex composite structures

## Further Reading

- **Book:** "Head First Design Patterns" (Chapter 9 - Iterator, Chapter 10 - Composite)
- **Iterator_and_Composite_Pattern.md**: Comprehensive 800+ line analysis with embedded systems examples
- **UML Diagrams**: Visual representation in UML/ directory
- **Design Principles**: See Iterator_and_Composite_Pattern.md for in-depth principle explanations

## License

This is an educational project based on "Head First Design Patterns" by Freeman & Robson.

## Author

Converted to modern C++20 as part of design patterns learning journey.
