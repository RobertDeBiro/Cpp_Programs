#ifndef SOLD_STATE_H
#define SOLD_STATE_H

#include "State.h"
#include <iostream>

// Forward declaration
class GumballMachine;

/**
 * @brief Concrete state representing the "dispensing gumball" state
 *
 * In this state:
 * - insertQuarter() does nothing (already dispensing)
 * - ejectQuarter() does nothing (already committed)
 * - turnCrank() does nothing (already turned)
 * - dispense() releases gumball and transitions to NoQuarterState or SoldOutState
 */
class SoldState : public State {
public:
    void insertQuarter([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "Please wait, we're already giving you a gumball\n";
    }

    void ejectQuarter([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "Sorry, you already turned the crank\n";
    }

    void turnCrank([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "Turning twice doesn't get you another gumball!\n";
    }

    void dispense(GumballMachine* machine) override {
        machine->releaseBall();

        if (machine->getCount() > 0) {
            machine->setState(machine->getNoQuarterState());
        } else {
            std::cout << "Oops, out of gumballs!\n";
            machine->setState(machine->getSoldOutState());
        }
    }
};

#endif // SOLD_STATE_H
