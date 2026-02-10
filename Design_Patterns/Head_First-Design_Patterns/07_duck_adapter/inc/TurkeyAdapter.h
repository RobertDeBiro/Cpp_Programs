#ifndef TURKEYADAPTER_H
#define TURKEYADAPTER_H

#include "Duck.h"
#include "Turkey.h"

/**
 * @brief Adapter - Makes Turkey look like Duck
 *
 * This is the Adapter class in the Adapter pattern.
 * It adapts the Turkey interface to the Duck interface.
 *
 * How it works:
 * 1. Implements the Target interface (Duck)
 * 2. Holds a reference to the Adaptee (Turkey)
 * 3. Translates Target method calls to Adaptee method calls
 *
 * This uses the Object Adapter approach (composition).
 * The adapter HAS-A Turkey and IS-A Duck.
 */
class TurkeyAdapter : public Duck {
private:
    Turkey* turkey;  // Reference to adaptee (non-owning)

public:
    /**
     * @brief Constructor - binds adapter to turkey adaptee
     * @param t Pointer to Turkey to adapt (adapter does not take ownership)
     */
    explicit TurkeyAdapter(Turkey* t) : turkey(t) {
        if (!t) {
            throw std::invalid_argument("Turkey cannot be null");
        }
    }

    /**
     * @brief Adapts Duck's quack() to Turkey's gobble()
     *
     * When client calls quack() expecting duck behavior,
     * we translate this to the turkey's gobble() method.
     */
    void quack() override {
        turkey->gobble();  // Translate: quack → gobble
    }

    /**
     * @brief Adapts Duck's fly() to Turkey's fly()
     *
     * Turkeys can only fly short distances, so to make up for
     * a duck's longer flight, we call the turkey's fly() method
     * multiple times.
     *
     * This demonstrates that adapters can do more than simple
     * 1-to-1 method mapping - they can adapt behavior as needed.
     */
    void fly() override {
        // Turkeys fly in short spurts
        // Call turkey's fly() five times to match duck's flying distance
        for (int i = 0; i < 5; ++i) {
            turkey->fly();
        }
    }
};

#endif // TURKEYADAPTER_H
