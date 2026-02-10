#include "CoffeeWithHook.h"
#include "TeaWithHook.h"
#include <iostream>

/**
 * @file main.cpp
 * @brief Demonstration of the Template Method Pattern with hooks
 *
 * This example shows how the Template Method pattern:
 * 1. Defines algorithm skeleton in base class (prepareRecipe)
 * 2. Lets subclasses implement specific steps (brew, addCondiments)
 * 3. Uses hooks for optional behavior (customerWantsCondiments)
 *
 * Key Concepts:
 * - Template Method: Non-virtual method that defines algorithm structure
 * - Abstract Methods: Pure virtual methods subclasses must implement
 * - Concrete Methods: Default implementations in base class
 * - Hooks: Virtual methods with default behavior, optional to override
 * - Hollywood Principle: "Don't call us, we'll call you"
 */

int main() {
    std::cout << "========================================\n";
    std::cout << "  Template Method Pattern Demo\n";
    std::cout << "  Caffeine Beverage with Hook\n";
    std::cout << "========================================\n\n";

    // Create tea beverage
    TeaWithHook teaHook;

    // Create coffee beverage
    CoffeeWithHook coffeeHook;

    // Prepare tea
    std::cout << "Making tea...\n";
    std::cout << "----------------------------------------\n";
    teaHook.prepareRecipe();
    // Template method calls:
    // 1. boilWater() - concrete method (base class)
    // 2. brew() - abstract method (TeaWithHook implementation)
    // 3. pourInCup() - concrete method (base class)
    // 4. customerWantsCondiments() - hook (TeaWithHook override)
    //    If true: addCondiments() - abstract method (TeaWithHook implementation)

    std::cout << "\n";

    // Prepare coffee
    std::cout << "Making coffee...\n";
    std::cout << "----------------------------------------\n";
    coffeeHook.prepareRecipe();
    // Template method calls:
    // 1. boilWater() - concrete method (base class)
    // 2. brew() - abstract method (CoffeeWithHook implementation)
    // 3. pourInCup() - concrete method (base class)
    // 4. customerWantsCondiments() - hook (CoffeeWithHook override)
    //    If true: addCondiments() - abstract method (CoffeeWithHook implementation)

    std::cout << "\n========================================\n";
    std::cout << "Pattern Benefits Demonstrated:\n";
    std::cout << "========================================\n";
    std::cout << "1. Algorithm defined once in base class\n";
    std::cout << "   - prepareRecipe() not duplicated\n";
    std::cout << "2. Common steps implemented once\n";
    std::cout << "   - boilWater() and pourInCup() shared\n";
    std::cout << "3. Subclasses only implement variations\n";
    std::cout << "   - brew() and addCondiments() specific\n";
    std::cout << "4. Hooks enable optional customization\n";
    std::cout << "   - customerWantsCondiments() can ask user\n";
    std::cout << "5. Algorithm structure protected\n";
    std::cout << "   - Subclasses cannot change step order\n";
    std::cout << "6. Hollywood Principle in action\n";
    std::cout << "   - Base class calls subclass methods\n";
    std::cout << "========================================\n";

    return 0;
}
