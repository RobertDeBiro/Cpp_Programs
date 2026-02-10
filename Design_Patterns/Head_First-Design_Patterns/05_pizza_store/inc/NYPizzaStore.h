#ifndef NYPIZZASTORE_H
#define NYPIZZASTORE_H

#include "PizzaStore.h"
#include "NYStyleCheesePizza.h"
#include "NYStylePepperoniPizza.h"
#include <memory>

/**
 * @brief Concrete Creator - New York Pizza Store
 *
 * Overrides factory method to create NY-style pizzas.
 * Encapsulates knowledge of which concrete NY pizza classes to instantiate.
 */
class NYPizzaStore : public PizzaStore {
protected:
    /**
     * @brief Factory method implementation for NY pizzas
     *
     * Creates NY-style pizzas based on type string.
     *
     * @param type Pizza type ("cheese", "pepperoni", etc.)
     * @return Unique pointer to NY-style pizza, or nullptr if type is unknown
     */
    std::unique_ptr<Pizza> createPizza(const std::string& type) override {
        if (type == "cheese") {
            return std::make_unique<NYStyleCheesePizza>();
        } else if (type == "pepperoni") {
            return std::make_unique<NYStylePepperoniPizza>();
        }

        // Unknown type - return nullptr
        return nullptr;
    }
};

#endif // NYPIZZASTORE_H
