#ifndef MENU_H
#define MENU_H

#include <memory>

// Forward declaration
class Iterator;

/**
 * @brief Interface for menu collections
 *
 * Defines the contract that all menus must follow.
 * Each menu must be able to create an iterator for its items.
 */
class Menu {
public:
    virtual ~Menu() = default;

    /**
     * @brief Factory method for creating an iterator over menu items
     * @return Unique pointer to an Iterator instance
     */
    virtual std::unique_ptr<Iterator> createIterator() = 0;
};

#endif // MENU_H
