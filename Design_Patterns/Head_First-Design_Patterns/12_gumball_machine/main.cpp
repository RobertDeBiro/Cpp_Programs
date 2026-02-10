#include "GumballMachine.h"
#include <iostream>

/**
 * @brief Demonstrate the State Pattern with a gumball machine
 *
 * This program shows how the State Pattern encapsulates state-specific behavior
 * into separate state objects, eliminating conditional logic and making the
 * code more maintainable and extensible.
 *
 * Key demonstrations:
 * 1. Normal operation (insert quarter, turn crank, get gumball)
 * 2. Invalid operations in each state (insert when has quarter, etc.)
 * 3. Winner state (1 in 10 chance of getting 2 gumballs)
 * 4. Running out of gumballs
 * 5. Refilling the machine
 */

void separator() {
    std::cout << "\n" << std::string(60, '=') << "\n\n";
}

void testBasicOperation() {
    std::cout << "TEST 1: Basic Operation - Insert Quarter and Get Gumball\n";
    separator();

    GumballMachine machine(5);
    machine.printStatus();

    std::cout << "\n>> Inserting quarter...\n";
    machine.insertQuarter();

    std::cout << "\n>> Turning crank...\n";
    machine.turnCrank();

    machine.printStatus();
}

void testInvalidOperations() {
    std::cout << "TEST 2: Invalid Operations\n";
    separator();

    GumballMachine machine(3);

    std::cout << ">> Trying to eject quarter without inserting one:\n";
    machine.ejectQuarter();

    std::cout << "\n>> Trying to turn crank without inserting quarter:\n";
    machine.turnCrank();

    std::cout << "\n>> Inserting quarter...\n";
    machine.insertQuarter();

    std::cout << "\n>> Trying to insert another quarter:\n";
    machine.insertQuarter();

    std::cout << "\n>> Ejecting quarter...\n";
    machine.ejectQuarter();

    machine.printStatus();
}

void testRunningOut() {
    std::cout << "TEST 3: Running Out of Gumballs\n";
    separator();

    GumballMachine machine(2);
    machine.printStatus();

    std::cout << "\n>> First purchase:\n";
    machine.insertQuarter();
    machine.turnCrank();

    std::cout << "\n>> Second purchase (should run out):\n";
    machine.insertQuarter();
    machine.turnCrank();

    machine.printStatus();

    std::cout << "\n>> Trying to use sold out machine:\n";
    machine.insertQuarter();
    machine.turnCrank();
}

void testRefill() {
    std::cout << "TEST 4: Refilling the Machine\n";
    separator();

    GumballMachine machine(1);
    machine.printStatus();

    std::cout << "\n>> Using last gumball:\n";
    machine.insertQuarter();
    machine.turnCrank();

    machine.printStatus();

    std::cout << "\n>> Refilling with 10 gumballs:\n";
    machine.refill(10);

    machine.printStatus();

    std::cout << "\n>> Using refilled machine:\n";
    machine.insertQuarter();
    machine.turnCrank();

    machine.printStatus();
}

void testWinnerScenario() {
    std::cout << "TEST 5: Looking for a Winner (1 in 10 chance)\n";
    separator();

    GumballMachine machine(10);
    machine.printStatus();

    std::cout << "\n>> Making multiple purchases to try to win:\n";
    std::cout << "(Note: There's a 1 in 10 chance of winning 2 gumballs)\n\n";

    // Make several purchases to potentially see a winner
    for (int i = 1; i <= 15 && machine.getCount() > 0; i++) {
        std::cout << "--- Purchase " << i << " ---\n";
        machine.insertQuarter();
        machine.turnCrank();
        std::cout << "Gumballs remaining: " << machine.getCount() << "\n\n";
    }

    machine.printStatus();
}

void testStateTransitions() {
    std::cout << "TEST 6: Demonstrating All State Transitions\n";
    separator();

    GumballMachine machine(3);

    std::cout << "State Transition Demo:\n";
    std::cout << "Initial state: NO_QUARTER\n";
    machine.printStatus();

    std::cout << "\n>> Transition: NO_QUARTER -> HAS_QUARTER (insertQuarter)\n";
    machine.insertQuarter();

    std::cout << "\n>> Transition: HAS_QUARTER -> NO_QUARTER (ejectQuarter)\n";
    machine.ejectQuarter();
    machine.printStatus();

    std::cout << "\n>> Transition: NO_QUARTER -> HAS_QUARTER -> SOLD -> NO_QUARTER\n";
    machine.insertQuarter();
    machine.turnCrank();
    machine.printStatus();

    std::cout << "\n>> Transition to SOLD_OUT state:\n";
    machine.insertQuarter();
    machine.turnCrank();
    machine.insertQuarter();
    machine.turnCrank();
    machine.printStatus();
}

int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║         STATE PATTERN DEMONSTRATION                        ║\n";
    std::cout << "║         Gumball Machine Example                            ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";

    testBasicOperation();
    separator();

    testInvalidOperations();
    separator();

    testRunningOut();
    separator();

    testRefill();
    separator();

    testWinnerScenario();
    separator();

    testStateTransitions();

    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  KEY BENEFITS OF STATE PATTERN:                           ║\n";
    std::cout << "║  1. Eliminates conditional logic (no if-else chains)      ║\n";
    std::cout << "║  2. Localizes state-specific behavior                     ║\n";
    std::cout << "║  3. Makes state transitions explicit                      ║\n";
    std::cout << "║  4. Easy to add new states (Open/Closed Principle)        ║\n";
    std::cout << "║  5. Each state is independently testable                  ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";

    return 0;
}
