#ifndef CHICAGOSTYLEPEPPERONIPIZZA_H
#define CHICAGOSTYLEPEPPERONIPIZZA_H

#include "Pizza.h"

/**
 * @brief Concrete Product - Chicago Style Pepperoni Pizza
 *
 * Implements Chicago-specific pepperoni pizza characteristics.
 */
class ChicagoStylePepperoniPizza : public Pizza {
public:
    explicit ChicagoStylePepperoniPizza() {
        name = "Chicago Style Pepperoni Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";

        toppings.push_back("Shredded Mozzarella Cheese");
        toppings.push_back("Black Olives");
        toppings.push_back("Spinach");
        toppings.push_back("Eggplant");
        toppings.push_back("Sliced Pepperoni");
    }

    ~ChicagoStylePepperoniPizza() override = default;

    /**
     * @brief Chicago style uses square slices instead of diagonal
     */
    void cut() override {
        std::cout << "Cutting the pizza into square slices" << std::endl;
    }
};

#endif // CHICAGOSTYLEPEPPERONIPIZZA_H
