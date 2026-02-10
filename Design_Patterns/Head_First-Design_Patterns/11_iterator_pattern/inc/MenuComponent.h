#ifndef MENU_COMPONENT_H
#define MENU_COMPONENT_H

#include <string>
#include <stdexcept>
#include <memory>

// Forward declaration
class Iterator;

/**
 * @brief Component interface for the Composite Pattern
 *
 * Defines operations for both leaf (MenuItem) and composite (Menu) objects.
 * Provides default implementations that throw exceptions for operations
 * that don't make sense for a particular component type.
 *
 * This allows treating individual objects and compositions uniformly.
 */
class MenuComponent {
public:
    virtual ~MenuComponent() = default;

    // Composite methods - for managing children
    virtual void add(std::unique_ptr<MenuComponent> /*component*/) {
        throw std::runtime_error("Unsupported operation");
    }

    virtual void remove(MenuComponent* /*component*/) {
        throw std::runtime_error("Unsupported operation");
    }

    virtual MenuComponent* getChild(size_t /*index*/) {
        throw std::runtime_error("Unsupported operation");
    }

    // Leaf methods - for menu item properties
    [[nodiscard]] virtual std::string getName() const {
        throw std::runtime_error("Unsupported operation");
    }

    [[nodiscard]] virtual std::string getDescription() const {
        throw std::runtime_error("Unsupported operation");
    }

    [[nodiscard]] virtual double getPrice() const {
        throw std::runtime_error("Unsupported operation");
    }

    [[nodiscard]] virtual bool isVegetarian() const {
        throw std::runtime_error("Unsupported operation");
    }

    // Operation method - both Menu and MenuItem implement this
    virtual void print() const {
        throw std::runtime_error("Unsupported operation");
    }

    // Iterator support - for iterating through composite structures
    virtual std::unique_ptr<Iterator> createIterator() {
        throw std::runtime_error("Unsupported operation");
    }
};

#endif // MENU_COMPONENT_H
