#ifndef HAS_QUARTER_STATE_H
#define HAS_QUARTER_STATE_H

#include "State.h"
#include <iostream>
#include <random>
#include <chrono>

// Forward declaration
class GumballMachine;

/**
 * @brief Concrete state representing the "quarter inserted" state
 *
 * In this state:
 * - insertQuarter() does nothing (already has quarter)
 * - ejectQuarter() returns quarter and transitions to NoQuarterState
 * - turnCrank() checks for winner and transitions to WinnerState or SoldState
 * - dispense() does nothing (inappropriate action)
 */
class HasQuarterState : public State {
private:
    std::mt19937 randomGenerator;
    std::uniform_int_distribution<int> distribution;

public:
    HasQuarterState()
        : randomGenerator(static_cast<unsigned int>(
            std::chrono::system_clock::now().time_since_epoch().count())),
          distribution(0, 9) {
    }

    void insertQuarter([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "You can't insert another quarter\n";
    }

    void ejectQuarter(GumballMachine* machine) override {
        std::cout << "Quarter returned\n";
        machine->setState(machine->getNoQuarterState());
    }

    void turnCrank(GumballMachine* machine) override {
        std::cout << "You turned...\n";

        // 1 in 10 chance of winning (if there are at least 2 gumballs)
        int winner = distribution(randomGenerator);

        if (winner == 0 && machine->getCount() > 1) {
            machine->setState(machine->getWinnerState());
        } else {
            machine->setState(machine->getSoldState());
        }
    }

    void dispense([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "No gumball dispensed\n";
    }
};

#endif // HAS_QUARTER_STATE_H
