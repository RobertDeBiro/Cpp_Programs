#ifndef PIZZASTORE_H
#define PIZZASTORE_H

#include "Pizza.h"
#include <memory>
#include <string>

/**
 * @brief Abstract Creator in Factory Method Pattern
 *
 * Defines the factory method createPizza() that subclasses override
 * to instantiate concrete products. The orderPizza() method is a
 * template method that orchestrates the pizza ordering workflow.
 */
class PizzaStore {
public:
    virtual ~PizzaStore() = default;

    /**
     * @brief Template method for ordering pizzas
     *
     * Defines the invariant algorithm for pizza ordering:
     * 1. Create pizza (via factory method - the varying step)
     * 2. Prepare pizza
     * 3. Bake pizza
     * 4. Cut pizza
     * 5. Box pizza
     *
     * @param type The type of pizza to order (e.g., "cheese", "pepperoni")
     * @return Unique pointer to the created pizza (ownership transferred to caller)
     */
    std::unique_ptr<Pizza> orderPizza(const std::string& type) {
        // Factory method - polymorphic dispatch to concrete creator
        auto pizza = createPizza(type);

        if (pizza) {
            // Template method - invariant steps
            pizza->prepare();
            pizza->bake();
            pizza->cut();
            pizza->box();
        }

        return pizza;
    }

protected:
    /**
     * @brief Factory method - subclasses override to create specific products
     *
     * This is the "hook" that subclasses implement to instantiate
     * region-specific pizzas. Marked protected because it's an
     * implementation detail - clients should call orderPizza() instead.
     *
     * @param type The type of pizza to create
     * @return Unique pointer to newly created pizza, or nullptr if type is invalid
     */
    virtual std::unique_ptr<Pizza> createPizza(const std::string& type) = 0;
};

#endif // PIZZASTORE_H
