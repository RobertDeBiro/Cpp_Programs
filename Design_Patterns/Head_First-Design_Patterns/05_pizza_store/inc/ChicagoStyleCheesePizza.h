#ifndef CHICAGOSTYLECHEESEPIZZA_H
#define CHICAGOSTYLECHEESEPIZZA_H

#include "Pizza.h"

/**
 * @brief Concrete Product - Chicago Style Deep Dish Cheese Pizza
 *
 * Implements Chicago-specific pizza characteristics:
 * - Extra thick crust (deep dish)
 * - Plum tomato sauce
 * - Shredded Mozzarella cheese
 * - Square cut slices (overrides cut method)
 */
class ChicagoStyleCheesePizza : public Pizza {
public:
    explicit ChicagoStyleCheesePizza() {
        name = "Chicago Style Deep Dish Cheese Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";

        toppings.push_back("Shredded Mozzarella Cheese");
    }

    ~ChicagoStyleCheesePizza() override = default;

    /**
     * @brief Chicago style uses square slices instead of diagonal
     */
    void cut() override {
        std::cout << "Cutting the pizza into square slices" << std::endl;
    }
};

#endif // CHICAGOSTYLECHEESEPIZZA_H
