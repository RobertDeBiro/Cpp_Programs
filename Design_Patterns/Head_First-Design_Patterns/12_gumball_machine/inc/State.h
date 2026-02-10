#ifndef STATE_H
#define STATE_H

// Forward declaration to avoid circular dependency
class GumballMachine;

/**
 * @brief State interface - defines the interface for state-dependent operations
 *
 * Each concrete state implements these methods to define behavior specific to that state.
 * The context (GumballMachine) delegates to the current state object.
 */
class State {
public:
    virtual ~State() = default;

    /**
     * @brief Handle quarter insertion
     * @param machine Pointer to the context (GumballMachine)
     */
    virtual void insertQuarter(GumballMachine* machine) = 0;

    /**
     * @brief Handle quarter ejection request
     * @param machine Pointer to the context (GumballMachine)
     */
    virtual void ejectQuarter(GumballMachine* machine) = 0;

    /**
     * @brief Handle crank turn
     * @param machine Pointer to the context (GumballMachine)
     */
    virtual void turnCrank(GumballMachine* machine) = 0;

    /**
     * @brief Handle gumball dispensing
     * @param machine Pointer to the context (GumballMachine)
     */
    virtual void dispense(GumballMachine* machine) = 0;
};

#endif // STATE_H
