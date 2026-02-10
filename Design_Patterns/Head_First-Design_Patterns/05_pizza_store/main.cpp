/**
 * @file main.cpp
 * @brief Factory Method Pattern - Pizza Store Demonstration
 *
 * Demonstrates the Factory Method pattern where:
 * - PizzaStore is the Abstract Creator with template method orderPizza()
 * - NYPizzaStore and ChicagoPizzaStore are Concrete Creators
 * - Pizza is the Abstract Product
 * - NYStyleCheesePizza, ChicagoStyleCheesePizza, etc. are Concrete Products
 *
 * Key Points:
 * - High-level orderPizza() depends only on Pizza interface (Dependency Inversion)
 * - Subclasses decide which concrete pizza to instantiate (Factory Method)
 * - Adding new regional stores doesn't modify existing code (Open/Closed Principle)
 * - Each store encapsulates its pizza creation logic (Single Responsibility)
 */

#include "PizzaStore.h"
#include "NYPizzaStore.h"
#include "ChicagoPizzaStore.h"
#include <iostream>
#include <memory>

int main() {
    std::cout << "=== Pizza Store Factory Method Demonstration ===" << std::endl;
    std::cout << std::endl;

    // Create store instances
    // Note: PizzaStore* depends only on abstract PizzaStore interface
    std::unique_ptr<PizzaStore> nyStore = std::make_unique<NYPizzaStore>();
    std::unique_ptr<PizzaStore> chicagoStore = std::make_unique<ChicagoPizzaStore>();

    // Order 1: NY Style Cheese Pizza
    std::cout << "--- Ethan's Order (NY Store) ---" << std::endl;
    auto pizza = nyStore->orderPizza("cheese");
    if (pizza) {
        std::cout << "Ethan ordered a " << pizza->getName() << std::endl;
    }
    std::cout << std::endl;

    // Order 2: Chicago Style Cheese Pizza
    std::cout << "--- Joel's Order (Chicago Store) ---" << std::endl;
    pizza = chicagoStore->orderPizza("cheese");
    if (pizza) {
        std::cout << "Joel ordered a " << pizza->getName() << std::endl;
    }
    std::cout << std::endl;

    // Order 3: NY Style Pepperoni Pizza
    std::cout << "--- Sarah's Order (NY Store) ---" << std::endl;
    pizza = nyStore->orderPizza("pepperoni");
    if (pizza) {
        std::cout << "Sarah ordered a " << pizza->getName() << std::endl;
    }
    std::cout << std::endl;

    // Order 4: Chicago Style Pepperoni Pizza
    std::cout << "--- Mike's Order (Chicago Store) ---" << std::endl;
    pizza = chicagoStore->orderPizza("pepperoni");
    if (pizza) {
        std::cout << "Mike ordered a " << pizza->getName() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "=== Demonstration Complete ===" << std::endl;
    std::cout << std::endl;

    std::cout << "Key Observations:" << std::endl;
    std::cout << "1. orderPizza() workflow is identical for all stores (Template Method)" << std::endl;
    std::cout << "2. Each store creates its region-specific pizzas (Factory Method)" << std::endl;
    std::cout << "3. Chicago pizzas use square cuts, NY pizzas use diagonal cuts" << std::endl;
    std::cout << "4. Main() depends only on abstract PizzaStore and Pizza interfaces" << std::endl;
    std::cout << "5. Adding California store wouldn't modify existing code (Open/Closed)" << std::endl;

    return 0;
}
