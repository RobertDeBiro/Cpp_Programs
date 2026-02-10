#ifndef WAITRESS_H
#define WAITRESS_H

#include "Menu.h"
#include "MenuItem.h"
#include "Iterator.h"
#include <vector>
#include <memory>
#include <iostream>

/**
 * @brief Client class that uses iterators to traverse menu collections
 *
 * Demonstrates how the Iterator Pattern allows uniform access to different
 * collection types without knowing their internal implementation.
 */
class Waitress {
private:
    std::vector<Menu*> m_menus;

    void printMenu(Iterator* iterator) const {
        while (iterator->hasNext()) {
            MenuItem* menuItem = iterator->next();
            if (menuItem != nullptr) {
                menuItem->print();
            }
        }
    }

public:
    Waitress(std::vector<Menu*> menus) : m_menus(std::move(menus)) {}

    void printMenu() const {
        std::cout << "\nMENU\n----\n";

        std::vector<std::string> menuNames = {"BREAKFAST", "LUNCH", "DINNER"};

        for (size_t i = 0; i < m_menus.size() && i < menuNames.size(); ++i) {
            std::cout << "\n" << menuNames[i] << "\n";
            auto iterator = m_menus[i]->createIterator();
            printMenu(iterator.get());
        }
    }

    void printVegetarianMenu() const {
        std::cout << "\nVEGETARIAN MENU\n---------------\n";

        for (auto* menu : m_menus) {
            auto iterator = menu->createIterator();
            while (iterator->hasNext()) {
                MenuItem* menuItem = iterator->next();
                if (menuItem != nullptr && menuItem->isVegetarian()) {
                    menuItem->print();
                }
            }
        }
    }

    bool isItemVegetarian(const std::string& name) const {
        for (auto* menu : m_menus) {
            auto iterator = menu->createIterator();
            while (iterator->hasNext()) {
                MenuItem* menuItem = iterator->next();
                if (menuItem != nullptr && menuItem->getName() == name) {
                    return menuItem->isVegetarian();
                }
            }
        }
        return false;
    }
};

#endif // WAITRESS_H
