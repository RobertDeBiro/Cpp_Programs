#ifndef DINER_MENU_H
#define DINER_MENU_H

#include "Menu.h"
#include "MenuItem.h"
#include "Iterator.h"
#include <array>
#include <memory>

/**
 * @brief Concrete menu using fixed-size array storage
 *
 * Demonstrates the Iterator Pattern by using a fixed array internally
 * while providing iterator-based access to clients.
 */
class DinerMenu : public Menu {
private:
    static constexpr size_t MAX_ITEMS = 10;
    std::array<std::unique_ptr<MenuItem>, MAX_ITEMS> m_menuItems;
    size_t m_numberOfItems{0};

    /**
     * @brief Concrete iterator for array-based menu
     */
    class DinerMenuIterator : public Iterator {
    private:
        const std::array<std::unique_ptr<MenuItem>, MAX_ITEMS>& m_items;
        size_t m_position{0};

    public:
        explicit DinerMenuIterator(const std::array<std::unique_ptr<MenuItem>, MAX_ITEMS>& items)
            : m_items(items) {}

        bool hasNext() const override {
            return m_position < MAX_ITEMS && m_items[m_position] != nullptr;
        }

        MenuItem* next() override {
            if (hasNext()) {
                return m_items[m_position++].get();
            }
            return nullptr;
        }
    };

public:
    DinerMenu() {
        addItem("Vegetarian BLT",
                "(Fakin') Bacon with lettuce & tomato on whole wheat",
                true,
                2.99);

        addItem("BLT",
                "Bacon with lettuce & tomato on whole wheat",
                false,
                2.99);

        addItem("Soup of the day",
                "Soup of the day, with a side of potato salad",
                false,
                3.29);

        addItem("Hotdog",
                "A hot dog, with sauerkraut, relish, onions, topped with cheese",
                false,
                3.05);

        addItem("Steamed Veggies and Brown Rice",
                "Steamed vegetables over brown rice",
                true,
                3.99);

        addItem("Pasta",
                "Spaghetti with marinara sauce, and a slice of sourdough bread",
                true,
                3.89);
    }

    void addItem(const std::string& name, const std::string& description,
                 bool vegetarian, double price) {
        if (m_numberOfItems >= MAX_ITEMS) {
            std::cerr << "Sorry, menu is full! Can't add item to menu\n";
            return;
        }
        m_menuItems[m_numberOfItems++] =
            std::make_unique<MenuItem>(name, description, vegetarian, price);
    }

    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<DinerMenuIterator>(m_menuItems);
    }
};

#endif // DINER_MENU_H
