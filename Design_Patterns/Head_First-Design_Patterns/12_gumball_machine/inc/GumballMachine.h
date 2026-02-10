#ifndef GUMBALL_MACHINE_H
#define GUMBALL_MACHINE_H

#include "State.h"
#include <memory>
#include <string>
#include <iostream>

// Forward declarations of concrete states
class NoQuarterState;
class HasQuarterState;
class SoldState;
class SoldOutState;
class WinnerState;

/**
 * @brief Context class for the State Pattern - represents a gumball vending machine
 *
 * The GumballMachine maintains references to all possible state objects and
 * delegates all state-dependent operations to the current state object.
 *
 * This is the "Context" in the State Pattern:
 * - Maintains a reference to the current state
 * - Delegates state-dependent operations to the current state
 * - Provides helper methods for states to use (releaseBall, getCount)
 * - Provides access to state objects for state transitions
 */
class GumballMachine {
private:
    // All possible states (owned by the machine)
    std::unique_ptr<State> soldOutState;
    std::unique_ptr<State> noQuarterState;
    std::unique_ptr<State> hasQuarterState;
    std::unique_ptr<State> soldState;
    std::unique_ptr<State> winnerState;

    // Current state (non-owning pointer to one of the above)
    State* state;

    // Number of gumballs in the machine
    int count;

public:
    /**
     * @brief Construct a gumball machine with initial inventory
     * @param numberGumballs Initial number of gumballs
     */
    explicit GumballMachine(int numberGumballs);

    /**
     * @brief Insert a quarter - delegates to current state
     */
    void insertQuarter() {
        state->insertQuarter(this);
    }

    /**
     * @brief Eject quarter - delegates to current state
     */
    void ejectQuarter() {
        state->ejectQuarter(this);
    }

    /**
     * @brief Turn crank - delegates to current state
     */
    void turnCrank() {
        state->turnCrank(this);
        // Automatically dispense after crank is turned
        state->dispense(this);
    }

    /**
     * @brief Change the current state
     * @param newState Pointer to the new state
     */
    void setState(State* newState) {
        state = newState;
    }

    /**
     * @brief Helper method to release a gumball
     *
     * This is called by state objects during dispensing.
     * Decrements the count and prints a message.
     */
    void releaseBall() {
        std::cout << "A gumball comes rolling out the slot...\n";
        if (count > 0) {
            count--;
        }
    }

    /**
     * @brief Get the current gumball count
     * @return Number of gumballs remaining
     */
    int getCount() const {
        return count;
    }

    /**
     * @brief Refill the machine with gumballs
     * @param newCount Number of gumballs to add
     */
    void refill(int newCount) {
        count += newCount;
        std::cout << "The gumball machine was just refilled; its new count is: "
                  << count << "\n";
        if (count > 0) {
            state = noQuarterState.get();
        }
    }

    /**
     * @brief Get string representation of the machine's state
     * @return String describing the machine
     */
    std::string toString() const {
        std::string result = "\nMighty Gumball, Inc.\n";
        result += "C++-enabled Standing Gumball Model #2024\n";
        result += "Inventory: " + std::to_string(count) + " gumball";
        if (count != 1) {
            result += "s";
        }
        result += "\n";

        // Determine current state name
        if (state == soldOutState.get()) {
            result += "Machine is sold out\n";
        } else if (state == noQuarterState.get()) {
            result += "Machine is waiting for quarter\n";
        } else if (state == hasQuarterState.get()) {
            result += "Machine is waiting for turn of crank\n";
        } else if (state == soldState.get()) {
            result += "Machine is dispensing a gumball\n";
        } else if (state == winnerState.get()) {
            result += "Machine is dispensing TWO gumballs - YOU'RE A WINNER!\n";
        }

        return result;
    }

    // State getters for state transitions
    State* getNoQuarterState() {
        return noQuarterState.get();
    }

    State* getHasQuarterState() {
        return hasQuarterState.get();
    }

    State* getSoldState() {
        return soldState.get();
    }

    State* getSoldOutState() {
        return soldOutState.get();
    }

    State* getWinnerState() {
        return winnerState.get();
    }

    /**
     * @brief Print the machine's current status
     */
    void printStatus() const {
        std::cout << toString();
    }
};

// Include concrete state implementations
#include "NoQuarterState.h"
#include "HasQuarterState.h"
#include "SoldState.h"
#include "SoldOutState.h"
#include "WinnerState.h"

// GumballMachine constructor implementation (must be after state class definitions)
inline GumballMachine::GumballMachine(int numberGumballs) : count(numberGumballs) {
    // Create all state objects
    soldOutState = std::make_unique<SoldOutState>();
    noQuarterState = std::make_unique<NoQuarterState>();
    hasQuarterState = std::make_unique<HasQuarterState>();
    soldState = std::make_unique<SoldState>();
    winnerState = std::make_unique<WinnerState>();

    // Set initial state based on gumball count
    if (count > 0) {
        state = noQuarterState.get();
    } else {
        state = soldOutState.get();
    }
}

#endif // GUMBALL_MACHINE_H
