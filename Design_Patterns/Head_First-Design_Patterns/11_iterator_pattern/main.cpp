/**
 * @file main.cpp
 * @brief Demonstrates both Iterator and Composite Patterns
 *
 * Iterator Pattern: Provides uniform access to different collection types
 * Composite Pattern: Composes objects into tree structures for part-whole hierarchies
 */

#include <iostream>
#include <memory>
#include <vector>

// Iterator Pattern includes
#include "inc/MenuItem.h"
#include "inc/Iterator.h"
#include "inc/Menu.h"
#include "inc/PancakeHouseMenu.h"
#include "inc/DinerMenu.h"
#include "inc/CafeMenu.h"
#include "inc/Waitress.h"

// Composite Pattern includes
#include "inc/MenuComponent.h"
#include "inc/CompositeMenuItem.h"
#include "inc/CompositeMenu.h"
#include "inc/CompositeWaitress.h"

void printSeparator(const std::string& title) {
    std::cout << "\n";
    std::cout << "=============================================================================\n";
    std::cout << "  " << title << "\n";
    std::cout << "=============================================================================\n";
}

void demonstrateIteratorPattern() {
    printSeparator("ITERATOR PATTERN DEMONSTRATION");

    std::cout << "\nThe Iterator Pattern allows us to iterate over different collection types\n";
    std::cout << "(array, vector, map) through a uniform interface without exposing their\n";
    std::cout << "internal representation.\n";

    // Create menus with different internal representations
    PancakeHouseMenu pancakeHouseMenu;  // Uses std::vector
    DinerMenu dinerMenu;                // Uses std::array
    CafeMenu cafeMenu;                  // Uses std::map

    // Waitress works with all menus through the Iterator interface
    std::vector<Menu*> menus = {&pancakeHouseMenu, &dinerMenu, &cafeMenu};
    Waitress waitress(menus);

    // Print all menus
    waitress.printMenu();

    // Print only vegetarian items
    waitress.printVegetarianMenu();

    // Check if specific item is vegetarian
    std::cout << "\n--- Item Checks ---\n";
    std::cout << "Is 'Hotdog' vegetarian? "
              << (waitress.isItemVegetarian("Hotdog") ? "Yes" : "No") << "\n";
    std::cout << "Is 'Waffles' vegetarian? "
              << (waitress.isItemVegetarian("Waffles") ? "Yes" : "No") << "\n";

    std::cout << "\nKey Points:\n";
    std::cout << "1. Each menu uses a different collection type internally\n";
    std::cout << "2. Waitress doesn't know or care about the implementation\n";
    std::cout << "3. All menus provide a uniform Iterator interface\n";
    std::cout << "4. We can add new collection types without changing client code\n";
}

void demonstrateCompositePattern() {
    printSeparator("COMPOSITE PATTERN DEMONSTRATION");

    std::cout << "\nThe Composite Pattern allows us to build tree structures of objects\n";
    std::cout << "and treat individual objects and compositions uniformly.\n";
    std::cout << "This creates a part-whole hierarchy.\n\n";

    // Create the main menu (root composite)
    auto allMenus = std::make_unique<CompositeMenu>("ALL MENUS", "All menus combined");

    // Create pancake house menu (composite)
    auto pancakeMenu = std::make_unique<CompositeMenu>("PANCAKE HOUSE MENU", "Breakfast");
    pancakeMenu->add(std::make_unique<CompositeMenuItem>(
        "K&B's Pancake Breakfast",
        "Pancakes with scrambled eggs, and toast",
        true, 2.99));
    pancakeMenu->add(std::make_unique<CompositeMenuItem>(
        "Regular Pancake Breakfast",
        "Pancakes with fried eggs, sausage",
        false, 2.99));
    pancakeMenu->add(std::make_unique<CompositeMenuItem>(
        "Blueberry Pancakes",
        "Pancakes made with fresh blueberries",
        true, 3.49));
    pancakeMenu->add(std::make_unique<CompositeMenuItem>(
        "Waffles",
        "Waffles with your choice of blueberries or strawberries",
        true, 3.59));

    // Create diner menu (composite)
    auto dinerMenu = std::make_unique<CompositeMenu>("DINER MENU", "Lunch");
    dinerMenu->add(std::make_unique<CompositeMenuItem>(
        "Vegetarian BLT",
        "(Fakin') Bacon with lettuce & tomato on whole wheat",
        true, 2.99));
    dinerMenu->add(std::make_unique<CompositeMenuItem>(
        "BLT",
        "Bacon with lettuce & tomato on whole wheat",
        false, 2.99));
    dinerMenu->add(std::make_unique<CompositeMenuItem>(
        "Soup of the day",
        "Soup of the day, with a side of potato salad",
        false, 3.29));
    dinerMenu->add(std::make_unique<CompositeMenuItem>(
        "Hotdog",
        "A hot dog with sauerkraut, relish, onions, topped with cheese",
        false, 3.05));

    // Create dessert submenu (composite within composite)
    auto dessertMenu = std::make_unique<CompositeMenu>("DESSERT MENU", "Dessert of course!");
    dessertMenu->add(std::make_unique<CompositeMenuItem>(
        "Apple Pie",
        "Apple pie with a flakey crust, topped with vanilla ice cream",
        true, 1.59));
    dessertMenu->add(std::make_unique<CompositeMenuItem>(
        "Cheesecake",
        "Creamy New York cheesecake, with a chocolate graham crust",
        true, 1.99));
    dessertMenu->add(std::make_unique<CompositeMenuItem>(
        "Sorbet",
        "A scoop of raspberry and a scoop of lime",
        true, 1.89));

    // Add dessert menu to diner menu (nested composite)
    dinerMenu->add(std::move(dessertMenu));

    // Create cafe menu (composite)
    auto cafeMenu = std::make_unique<CompositeMenu>("CAFE MENU", "Dinner");
    cafeMenu->add(std::make_unique<CompositeMenuItem>(
        "Veggie Burger and Air Fries",
        "Veggie burger on a whole wheat bun, lettuce, tomato, and fries",
        true, 3.99));
    cafeMenu->add(std::make_unique<CompositeMenuItem>(
        "Soup of the day",
        "A cup of the soup of the day, with a side salad",
        false, 3.69));
    cafeMenu->add(std::make_unique<CompositeMenuItem>(
        "Burrito",
        "A large burrito with whole pinto beans, salsa, guacamole",
        true, 4.29));

    // Build the complete tree structure
    allMenus->add(std::move(pancakeMenu));
    allMenus->add(std::move(dinerMenu));
    allMenus->add(std::move(cafeMenu));

    // Create waitress with the composite structure
    CompositeWaitress waitress(allMenus.get());

    // Print the entire menu hierarchy
    waitress.printMenu();

    std::cout << "\nKey Points:\n";
    std::cout << "1. Menu items (leaves) and menus (composites) are treated uniformly\n";
    std::cout << "2. We can nest menus arbitrarily deep (e.g., dessert menu in diner menu)\n";
    std::cout << "3. print() operation works recursively on the entire tree\n";
    std::cout << "4. Client code doesn't distinguish between leaves and composites\n";
}

void demonstratePatternComparison() {
    printSeparator("PATTERN COMPARISON");

    std::cout << "\nIterator Pattern vs Composite Pattern:\n\n";

    std::cout << "ITERATOR PATTERN:\n";
    std::cout << "- Purpose: Provide sequential access to collection elements\n";
    std::cout << "- Structure: Flat collections (arrays, lists, maps)\n";
    std::cout << "- Focus: Traversal abstraction\n";
    std::cout << "- Hides: Internal collection representation\n";
    std::cout << "- Benefit: Uniform interface for different collection types\n\n";

    std::cout << "COMPOSITE PATTERN:\n";
    std::cout << "- Purpose: Compose objects into tree structures\n";
    std::cout << "- Structure: Hierarchical trees (part-whole hierarchies)\n";
    std::cout << "- Focus: Structural composition\n";
    std::cout << "- Hides: Difference between leaf and composite objects\n";
    std::cout << "- Benefit: Treat individual objects and compositions uniformly\n\n";

    std::cout << "WORKING TOGETHER:\n";
    std::cout << "- Composite can use Iterator to traverse its children\n";
    std::cout << "- Iterator can traverse a Composite structure\n";
    std::cout << "- Both promote loose coupling and Single Responsibility\n";
}

int main() {
    std::cout << "\n";
    std::cout << "*****************************************************************************\n";
    std::cout << "*                                                                           *\n";
    std::cout << "*              ITERATOR AND COMPOSITE PATTERNS DEMONSTRATION                *\n";
    std::cout << "*                                                                           *\n";
    std::cout << "*****************************************************************************\n";

    try {
        demonstrateIteratorPattern();
        demonstrateCompositePattern();
        demonstratePatternComparison();

        printSeparator("DEMONSTRATION COMPLETE");
        std::cout << "\nBoth patterns successfully demonstrated!\n\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << "\n";
        return 1;
    }
}
