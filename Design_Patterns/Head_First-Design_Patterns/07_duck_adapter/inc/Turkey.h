#ifndef TURKEY_H
#define TURKEY_H

/**
 * @brief Adaptee Interface - Turkey
 *
 * This is the existing interface that is INCOMPATIBLE with
 * what the client expects (Duck interface).
 *
 * In the Adapter pattern, this is called the "Adaptee".
 * Turkeys gobble instead of quack, and fly differently than ducks.
 */
class Turkey {
public:
    virtual ~Turkey() = default;

    /**
     * @brief Turkey gobbling behavior (NOT quacking)
     */
    virtual void gobble() = 0;

    /**
     * @brief Turkey flying behavior (short distance)
     */
    virtual void fly() = 0;
};

#endif // TURKEY_H
