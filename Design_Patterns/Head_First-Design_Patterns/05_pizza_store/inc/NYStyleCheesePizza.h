#ifndef NYSTYLECHEESEPIZZA_H
#define NYSTYLECHEESEPIZZA_H

#include "Pizza.h"

/**
 * @brief Concrete Product - NY Style Cheese Pizza
 *
 * Implements NY-specific pizza characteristics:
 * - Thin crust dough
 * - Marinara sauce
 * - Grated Reggiano cheese
 */
class NYStyleCheesePizza : public Pizza {
public:
    explicit NYStyleCheesePizza() {
        name = "NY Style Sauce and Cheese Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";

        toppings.push_back("Grated Reggiano Cheese");
    }

    ~NYStyleCheesePizza() override = default;
};

#endif // NYSTYLECHEESEPIZZA_H
