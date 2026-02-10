#ifndef DUCK_H
#define DUCK_H

/**
 * @brief Target Interface - Duck
 *
 * This is the interface that the client expects.
 * In the Adapter pattern, this is called the "Target" interface.
 *
 * The client code is written to work with this interface,
 * and we want to adapt other classes (like Turkey) to work
 * with code expecting this interface.
 */
class Duck {
public:
    virtual ~Duck() = default;

    /**
     * @brief Duck quacking behavior
     */
    virtual void quack() = 0;

    /**
     * @brief Duck flying behavior
     */
    virtual void fly() = 0;
};

#endif // DUCK_H
