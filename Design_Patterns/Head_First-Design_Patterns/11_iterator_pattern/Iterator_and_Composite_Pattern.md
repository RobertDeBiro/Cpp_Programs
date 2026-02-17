# Iterator and Composite Patterns - Comprehensive Analysis

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

![Bad Design: Direct Collection Exposure](UML/Bad_Direct_Collection_Exposure.puml)

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

![Bad Design: Mixed Leaf and Composite Handling](UML/Bad_Mixed_Leaf_Composite.puml)

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
