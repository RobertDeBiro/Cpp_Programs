/**
 * @file main.cpp
 * @brief Adapter Pattern - Duck/Turkey Adapter Demonstration
 *
 * Demonstrates the Adapter pattern where:
 * - Duck is the Target interface (what client expects)
 * - Turkey is the Adaptee interface (incompatible with target)
 * - TurkeyAdapter is the Adapter (makes Turkey compatible with Duck)
 * - testDuck() is the Client (works only with Duck interface)
 *
 * Key Points:
 * - Client code (testDuck) only knows about Duck interface
 * - TurkeyAdapter makes Turkey usable where Duck is expected
 * - Neither Duck nor Turkey needs modification
 * - Adapter translates interface and adapts behavior as needed
 *
 * This pattern is essential when:
 * - You have existing code with incompatible interface
 * - Cannot modify existing code (third-party, legacy, shared)
 * - Want to reuse existing functionality in new context
 */

#include "Duck.h"
#include "Turkey.h"
#include "MallardDuck.h"
#include "WildTurkey.h"
#include "TurkeyAdapter.h"
#include <iostream>
#include <memory>

/**
 * @brief Client function that expects Duck interface
 *
 * This represents client code that is written to work with
 * the Duck interface. It has no knowledge of Turkey or TurkeyAdapter.
 *
 * @param duck Pointer to Duck (or adapter implementing Duck interface)
 */
void testDuck(Duck* duck) {
    duck->quack();
    duck->fly();
}

int main() {
    std::cout << "=== Adapter Pattern - Duck/Turkey Demonstration ===" << std::endl;
    std::cout << std::endl;

    // Create a real duck
    std::unique_ptr<Duck> duck = std::make_unique<MallardDuck>();

    // Create a turkey (incompatible interface)
    std::unique_ptr<Turkey> turkey = std::make_unique<WildTurkey>();

    // Wrap the turkey in an adapter to make it look like a duck
    std::unique_ptr<Duck> turkeyAdapter = std::make_unique<TurkeyAdapter>(turkey.get());

    std::cout << "--- Testing Turkey directly (incompatible interface) ---" << std::endl;
    std::cout << "The Turkey says..." << std::endl;
    turkey->gobble();  // Turkey's native interface
    turkey->fly();
    std::cout << std::endl;

    std::cout << "--- Testing Duck (target interface) ---" << std::endl;
    std::cout << "The Duck says..." << std::endl;
    testDuck(duck.get());  // Real duck works with testDuck()
    std::cout << std::endl;

    std::cout << "--- Testing TurkeyAdapter (adapted interface) ---" << std::endl;
    std::cout << "The TurkeyAdapter says..." << std::endl;
    testDuck(turkeyAdapter.get());  // Adapted turkey works with testDuck()!
    std::cout << std::endl;

    std::cout << "=== Demonstration Complete ===" << std::endl;
    std::cout << std::endl;

    std::cout << "Key Observations:" << std::endl;
    std::cout << "1. testDuck() only knows about Duck interface, not Turkey" << std::endl;
    std::cout << "2. TurkeyAdapter makes Turkey usable where Duck is expected" << std::endl;
    std::cout << "3. Turkey's gobble() is adapted to Duck's quack()" << std::endl;
    std::cout << "4. Turkey's short fly() is called 5 times to match Duck's fly()" << std::endl;
    std::cout << "5. Neither Duck nor Turkey classes were modified" << std::endl;
    std::cout << "6. Client code (testDuck) remains unchanged" << std::endl;

    return 0;
}
