#ifndef SOLD_OUT_STATE_H
#define SOLD_OUT_STATE_H

#include "State.h"
#include <iostream>

/**
 * @brief Concrete state representing the "out of gumballs" state
 *
 * In this state:
 * - insertQuarter() does nothing (machine is empty)
 * - ejectQuarter() does nothing (no quarter to eject)
 * - turnCrank() does nothing (no gumballs available)
 * - dispense() does nothing (no gumballs available)
 */
class SoldOutState : public State {
public:
    void insertQuarter([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "You can't insert a quarter, the machine is sold out\n";
    }

    void ejectQuarter([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "You can't eject, you haven't inserted a quarter yet\n";
    }

    void turnCrank([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "You turned, but there are no gumballs\n";
    }

    void dispense([[maybe_unused]] GumballMachine* machine) override {
        std::cout << "No gumball dispensed\n";
    }
};

#endif // SOLD_OUT_STATE_H
