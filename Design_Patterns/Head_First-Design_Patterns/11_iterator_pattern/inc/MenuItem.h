#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <iostream>

/**
 * @brief Represents a single menu item with name, description, price, and vegetarian flag
 *
 * This is the element being iterated over in the Iterator Pattern.
 * In the Composite Pattern, this serves as the Leaf node.
 */
class MenuItem {
private:
    std::string m_name;
    std::string m_description;
    bool m_vegetarian;
    double m_price;

public:
    MenuItem(std::string name, std::string description, bool vegetarian, double price)
        : m_name(std::move(name))
        , m_description(std::move(description))
        , m_vegetarian(vegetarian)
        , m_price(price) {}

    [[nodiscard]] const std::string& getName() const { return m_name; }
    [[nodiscard]] const std::string& getDescription() const { return m_description; }
    [[nodiscard]] bool isVegetarian() const { return m_vegetarian; }
    [[nodiscard]] double getPrice() const { return m_price; }

    void print() const {
        std::cout << " " << m_name;
        if (m_vegetarian) {
            std::cout << "(v)";
        }
        std::cout << ", $" << m_price << "\n";
        std::cout << "    -- " << m_description << "\n";
    }
};

#endif // MENU_ITEM_H
