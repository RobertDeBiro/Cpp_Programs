#ifndef CHICAGOPIZZASTORE_H
#define CHICAGOPIZZASTORE_H

#include "PizzaStore.h"
#include "ChicagoStyleCheesePizza.h"
#include "ChicagoStylePepperoniPizza.h"
#include <memory>

/**
 * @brief Concrete Creator - Chicago Pizza Store
 *
 * Overrides factory method to create Chicago-style pizzas.
 * Encapsulates knowledge of which concrete Chicago pizza classes to instantiate.
 */
class ChicagoPizzaStore : public PizzaStore {
protected:
    /**
     * @brief Factory method implementation for Chicago pizzas
     *
     * Creates Chicago-style pizzas based on type string.
     *
     * @param type Pizza type ("cheese", "pepperoni", etc.)
     * @return Unique pointer to Chicago-style pizza, or nullptr if type is unknown
     */
    std::unique_ptr<Pizza> createPizza(const std::string& type) override {
        if (type == "cheese") {
            return std::make_unique<ChicagoStyleCheesePizza>();
        } else if (type == "pepperoni") {
            return std::make_unique<ChicagoStylePepperoniPizza>();
        }

        // Unknown type - return nullptr
        return nullptr;
    }
};

#endif // CHICAGOPIZZASTORE_H
