#ifndef NO_QUARTER_STATE_H
#define NO_QUARTER_STATE_H

#include "State.h"
#include <iostream>

// Forward declaration
class GumballMachine;

/**
 * @brief Concrete state representing the "no quarter inserted" state
 *
 * In this state:
 * - insertQuarter() transitions to HasQuarterState
 * - ejectQuarter() does nothing (no quarter to eject)
 * - turnCrank() does nothing (no payment)
 * - dispense() does nothing (no payment)
 */
class NoQuarterState : public State {
public:
    void insertQuarter(GumballMachine* machine) override {
        std::cout << "You inserted a quarter\n";
        machine->setState(machine->getHasQuarterState());
    }

    void ejectQuarter([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "You haven't inserted a quarter\n";
    }

    void turnCrank([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "You turned, but there's no quarter\n";
    }

    void dispense([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "You need to pay first\n";
    }
};

#endif // NO_QUARTER_STATE_H
