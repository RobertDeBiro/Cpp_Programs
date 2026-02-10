#ifndef CAFFEINE_BEVERAGE_WITH_HOOK_H
#define CAFFEINE_BEVERAGE_WITH_HOOK_H

#include <iostream>

/**
 * @brief Abstract base class for caffeine beverages using Template Method pattern
 *
 * This class defines the skeleton of the beverage preparation algorithm.
 * Subclasses must implement the varying steps (brew, addCondiments) while
 * the template method (prepareRecipe) controls the overall algorithm structure.
 *
 * Design Pattern: Template Method
 * - Template Method: prepareRecipe() (non-virtual, cannot be overridden)
 * - Abstract Methods: brew(), addCondiments() (must be implemented by subclasses)
 * - Concrete Methods: boilWater(), pourInCup() (default implementations)
 * - Hook: customerWantsCondiments() (optional override)
 */
class CaffeineBeverageWithHook {
public:
    /**
     * @brief Virtual destructor for proper polymorphic deletion
     */
    virtual ~CaffeineBeverageWithHook() = default;

    /**
     * @brief Template method that defines the beverage preparation algorithm
     *
     * This method is non-virtual (NVI idiom) to prevent subclasses from
     * overriding the algorithm structure. The algorithm is:
     * 1. Boil water
     * 2. Brew the beverage
     * 3. Pour into cup
     * 4. Add condiments (if customer wants them - hook)
     *
     * This enforces the Hollywood Principle: "Don't call us, we'll call you"
     * The template method calls the subclass methods, not vice versa.
     */
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();

        if (customerWantsCondiments()) {
            addCondiments();
        }
    }

protected:
    /**
     * @brief Abstract method: Brew the beverage (varying step)
     *
     * Subclasses must provide implementation for their specific brewing method.
     * Example: Coffee drips through filter, Tea steeps in water
     */
    virtual void brew() = 0;

    /**
     * @brief Abstract method: Add condiments (varying step)
     *
     * Subclasses must provide implementation for their specific condiments.
     * Example: Coffee adds milk and sugar, Tea adds lemon
     */
    virtual void addCondiments() = 0;

    /**
     * @brief Concrete method: Boil water (common step)
     *
     * Default implementation used by all beverages.
     * Subclasses typically don't need to override this.
     */
    void boilWater() {
        std::cout << "Boiling water\n";
    }

    /**
     * @brief Concrete method: Pour into cup (common step)
     *
     * Default implementation used by all beverages.
     * Subclasses typically don't need to override this.
     */
    void pourInCup() {
        std::cout << "Pouring into cup\n";
    }

    /**
     * @brief Hook: Determine if customer wants condiments
     *
     * This is a hook method - it provides a default behavior but subclasses
     * can override it to customize the algorithm without changing its structure.
     *
     * Default implementation returns true (assume customer wants condiments).
     * Subclasses can override to:
     * - Ask the user (interactive)
     * - Return false (no condiments)
     * - Use configuration/preferences
     *
     * @return true if condiments should be added, false otherwise
     */
    virtual bool customerWantsCondiments() {
        return true;
    }
};

#endif // CAFFEINE_BEVERAGE_WITH_HOOK_H
