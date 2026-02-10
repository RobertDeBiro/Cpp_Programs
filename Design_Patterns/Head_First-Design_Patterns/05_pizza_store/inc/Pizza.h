#ifndef PIZZA_H
#define PIZZA_H

#include <string>
#include <vector>
#include <iostream>

/**
 * @brief Abstract Product in Factory Method Pattern
 *
 * Defines the interface for objects created by the factory method.
 * Contains common pizza operations and properties.
 */
class Pizza {
protected:
    std::string name;
    std::string dough;
    std::string sauce;
    std::vector<std::string> toppings;

public:
    virtual ~Pizza() = default;

    /**
     * @brief Prepares the pizza (printing ingredients)
     *
     * Template method that can be overridden by subclasses
     * for specialized preparation.
     */
    virtual void prepare() {
        std::cout << "Preparing " << name << std::endl;
        std::cout << "Tossing dough..." << std::endl;
        std::cout << "Adding sauce..." << std::endl;
        std::cout << "Adding toppings: " << std::endl;
        for (const auto& topping : toppings) {
            std::cout << "   " << topping << std::endl;
        }
    }

    /**
     * @brief Bakes the pizza
     */
    virtual void bake() {
        std::cout << "Bake for 25 minutes at 350" << std::endl;
    }

    /**
     * @brief Cuts the pizza into slices
     *
     * Can be overridden for different cutting styles
     * (e.g., Chicago deep dish uses square slices).
     */
    virtual void cut() {
        std::cout << "Cutting the pizza into diagonal slices" << std::endl;
    }

    /**
     * @brief Boxes the pizza for delivery
     */
    virtual void box() {
        std::cout << "Place pizza in official PizzaStore box" << std::endl;
    }

    /**
     * @brief Gets the pizza name
     * @return Pizza name
     */
    std::string getName() const {
        return name;
    }

    // Prevent copying (pizzas are unique products)
    Pizza(const Pizza&) = delete;
    Pizza& operator=(const Pizza&) = delete;

    // Allow moving
    Pizza(Pizza&&) = default;
    Pizza& operator=(Pizza&&) = default;

protected:
    // Protected constructor (only derived classes can instantiate)
    Pizza() = default;
};

#endif // PIZZA_H
