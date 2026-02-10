#ifndef PANCAKE_HOUSE_MENU_H
#define PANCAKE_HOUSE_MENU_H

#include "Menu.h"
#include "MenuItem.h"
#include "Iterator.h"
#include <vector>
#include <memory>

/**
 * @brief Concrete menu using dynamic vector storage
 *
 * Demonstrates the Iterator Pattern by using a vector internally
 * while providing iterator-based access to clients.
 */
class PancakeHouseMenu : public Menu {
private:
    std::vector<std::unique_ptr<MenuItem>> m_menuItems;

    /**
     * @brief Concrete iterator for vector-based menu
     */
    class PancakeMenuIterator : public Iterator {
    private:
        const std::vector<std::unique_ptr<MenuItem>>& m_items;
        size_t m_position{0};

    public:
        explicit PancakeMenuIterator(const std::vector<std::unique_ptr<MenuItem>>& items)
            : m_items(items) {}

        bool hasNext() const override {
            return m_position < m_items.size();
        }

        MenuItem* next() override {
            if (hasNext()) {
                return m_items[m_position++].get();
            }
            return nullptr;
        }
    };

public:
    PancakeHouseMenu() {
        addItem("K&B's Pancake Breakfast",
                "Pancakes with scrambled eggs, and toast",
                true,
                2.99);

        addItem("Regular Pancake Breakfast",
                "Pancakes with fried eggs, sausage",
                false,
                2.99);

        addItem("Blueberry Pancakes",
                "Pancakes made with fresh blueberries, and blueberry syrup",
                true,
                3.49);

        addItem("Waffles",
                "Waffles with your choice of blueberries or strawberries",
                true,
                3.59);
    }

    void addItem(const std::string& name, const std::string& description,
                 bool vegetarian, double price) {
        m_menuItems.push_back(
            std::make_unique<MenuItem>(name, description, vegetarian, price));
    }

    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<PancakeMenuIterator>(m_menuItems);
    }
};

#endif // PANCAKE_HOUSE_MENU_H
