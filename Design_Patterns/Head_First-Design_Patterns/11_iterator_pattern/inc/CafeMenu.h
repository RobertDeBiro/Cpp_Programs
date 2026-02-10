#ifndef CAFE_MENU_H
#define CAFE_MENU_H

#include "Menu.h"
#include "MenuItem.h"
#include "Iterator.h"
#include <map>
#include <memory>
#include <string>

/**
 * @brief Concrete menu using map storage (key-value pairs)
 *
 * Demonstrates the Iterator Pattern with a map-based collection,
 * showing how different internal representations can be hidden
 * behind a common iterator interface.
 */
class CafeMenu : public Menu {
private:
    std::map<std::string, std::unique_ptr<MenuItem>> m_menuItems;

    /**
     * @brief Concrete iterator for map-based menu
     */
    class CafeMenuIterator : public Iterator {
    private:
        std::vector<MenuItem*> m_items;
        size_t m_position{0};

    public:
        explicit CafeMenuIterator(const std::map<std::string, std::unique_ptr<MenuItem>>& items) {
            // Convert map to vector for iteration
            m_items.reserve(items.size());
            for (const auto& pair : items) {
                m_items.push_back(pair.second.get());
            }
        }

        bool hasNext() const override {
            return m_position < m_items.size();
        }

        MenuItem* next() override {
            if (hasNext()) {
                return m_items[m_position++];
            }
            return nullptr;
        }
    };

public:
    CafeMenu() {
        addItem("Veggie Burger and Air Fries",
                "Veggie burger on a whole wheat bun, lettuce, tomato, and fries",
                true,
                3.99);

        addItem("Soup of the day",
                "A cup of the soup of the day, with a side salad",
                false,
                3.69);

        addItem("Burrito",
                "A large burrito, with whole pinto beans, salsa, guacamole",
                true,
                4.29);
    }

    void addItem(const std::string& name, const std::string& description,
                 bool vegetarian, double price) {
        auto item = std::make_unique<MenuItem>(name, description, vegetarian, price);
        m_menuItems[name] = std::move(item);
    }

    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<CafeMenuIterator>(m_menuItems);
    }
};

#endif // CAFE_MENU_H
