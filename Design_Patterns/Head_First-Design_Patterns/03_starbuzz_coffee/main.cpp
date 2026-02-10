#include "Beverage.h"
#include "Espresso.h"
#include "HouseBlend.h"
#include "DarkRoast.h"
#include "Decaf.h"
#include "Mocha.h"
#include "Whip.h"
#include "Soy.h"
#include <iostream>
#include <memory>
#include <iomanip>

int main() {
    std::cout << "=== Starbuzz Coffee Ordering System ===" << std::endl;
    std::cout << std::fixed << std::setprecision(2);  // Format prices
    std::cout << std::endl;

    // Order 1: Plain Espresso
    std::cout << "--- Order 1 ---" << std::endl;
    auto beverage1 = std::make_unique<Espresso>();
    std::cout << beverage1->getDescription()
              << " $" << beverage1->cost() << std::endl;
    std::cout << std::endl;

    // Order 2: Dark Roast with double Mocha and Whip
    std::cout << "--- Order 2 ---" << std::endl;
    std::unique_ptr<Beverage> beverage2 = std::make_unique<DarkRoast>();
    // Wrap with first Mocha
    beverage2 = std::make_unique<Mocha>(std::move(beverage2));
    // Wrap with second Mocha (double mocha!)
    beverage2 = std::make_unique<Mocha>(std::move(beverage2));
    // Wrap with Whip
    beverage2 = std::make_unique<Whip>(std::move(beverage2));
    std::cout << beverage2->getDescription()
              << " $" << beverage2->cost() << std::endl;
    std::cout << std::endl;

    // Order 3: House Blend with Soy, Mocha, and Whip
    std::cout << "--- Order 3 ---" << std::endl;
    std::unique_ptr<Beverage> beverage3 = std::make_unique<HouseBlend>();
    beverage3 = std::make_unique<Soy>(std::move(beverage3));
    beverage3 = std::make_unique<Mocha>(std::move(beverage3));
    beverage3 = std::make_unique<Whip>(std::move(beverage3));
    std::cout << beverage3->getDescription()
              << " $" << beverage3->cost() << std::endl;
    std::cout << std::endl;

    // Order 4: Decaf with Whip (keeping it simple)
    std::cout << "--- Order 4 ---" << std::endl;
    std::unique_ptr<Beverage> beverage4 = std::make_unique<Decaf>();
    beverage4 = std::make_unique<Whip>(std::move(beverage4));
    std::cout << beverage4->getDescription()
              << " $" << beverage4->cost() << std::endl;
    std::cout << std::endl;

    std::cout << "=== Demonstration Complete ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Note: Decorators wrap beverages dynamically at runtime!" << std::endl;
    std::cout << "No class explosion - each condiment is a separate decorator." << std::endl;

    // Automatic cleanup via unique_ptr - entire decorator chain deleted!
    return 0;
}
