#ifndef COMPOSITE_MENU_ITEM_H
#define COMPOSITE_MENU_ITEM_H

#include "MenuComponent.h"
#include "Iterator.h"
#include <iostream>
#include <string>
#include <memory>

/**
 * @brief Leaf component in the Composite Pattern
 *
 * Represents an individual menu item. Cannot contain other components.
 * Implements the operations that make sense for a leaf (getName, getPrice, etc.)
 * but throws exceptions for composite operations (add, remove, getChild).
 */
class CompositeMenuItem : public MenuComponent {
private:
    std::string m_name;
    std::string m_description;
    bool m_vegetarian;
    double m_price;

    /**
     * @brief Null Object pattern - Iterator that returns false for hasNext()
     *
     * Used because a leaf node has nothing to iterate over.
     * Better than returning nullptr which would require null checks.
     */
    class NullIterator : public Iterator {
    public:
        bool hasNext() const override { return false; }
        MenuItem* next() override { return nullptr; }
    };

public:
    CompositeMenuItem(std::string name, std::string description,
                      bool vegetarian, double price)
        : m_name(std::move(name))
        , m_description(std::move(description))
        , m_vegetarian(vegetarian)
        , m_price(price) {}

    [[nodiscard]] std::string getName() const override { return m_name; }
    [[nodiscard]] std::string getDescription() const override { return m_description; }
    [[nodiscard]] bool isVegetarian() const override { return m_vegetarian; }
    [[nodiscard]] double getPrice() const override { return m_price; }

    void print() const override {
        std::cout << "  " << m_name;
        if (m_vegetarian) {
            std::cout << "(v)";
        }
        std::cout << ", $" << m_price << "\n";
        std::cout << "     -- " << m_description << "\n";
    }

    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<NullIterator>();
    }
};

#endif // COMPOSITE_MENU_ITEM_H
