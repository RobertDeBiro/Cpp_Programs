#ifndef WINNER_STATE_H
#define WINNER_STATE_H

#include "State.h"
#include <iostream>

// Forward declaration
class GumballMachine;

/**
 * @brief Concrete state representing the "winner - dispense 2 gumballs" state
 *
 * In this state:
 * - insertQuarter() does nothing (already dispensing)
 * - ejectQuarter() does nothing (already committed)
 * - turnCrank() does nothing (already turned)
 * - dispense() releases TWO gumballs and transitions to NoQuarterState or SoldOutState
 *
 * This state demonstrates the extensibility of the State Pattern - it was added
 * to implement the "1 in 10 wins" game without modifying existing state classes.
 */
class WinnerState : public State {
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
        std::cout << "YOU'RE A WINNER! You get two gumballs for your quarter!\n";

        // Release first gumball
        machine->releaseBall();

        if (machine->getCount() == 0) {
            machine->setState(machine->getSoldOutState());
        } else {
            // Release second gumball
            machine->releaseBall();

            if (machine->getCount() > 0) {
                machine->setState(machine->getNoQuarterState());
            } else {
                std::cout << "Oops, out of gumballs!\n";
                machine->setState(machine->getSoldOutState());
            }
        }
    }
};

#endif // WINNER_STATE_H
