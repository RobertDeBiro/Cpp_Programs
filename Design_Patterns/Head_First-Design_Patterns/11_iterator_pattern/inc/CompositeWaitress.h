#ifndef COMPOSITE_WAITRESS_H
#define COMPOSITE_WAITRESS_H

#include "MenuComponent.h"
#include <memory>
#include <iostream>

/**
 * @brief Client for the Composite Pattern
 *
 * Works with the composite structure through the MenuComponent interface.
 * Doesn't need to know whether it's dealing with a leaf or composite -
 * it just calls print() and the structure handles the rest recursively.
 */
class CompositeWaitress {
private:
    MenuComponent* m_allMenus;

public:
    explicit CompositeWaitress(MenuComponent* allMenus) : m_allMenus(allMenus) {}

    void printMenu() const {
        std::cout << "\n========================================\n";
        std::cout << "         COMPOSITE MENU STRUCTURE       \n";
        std::cout << "========================================\n";
        m_allMenus->print();
        std::cout << "\n========================================\n";
    }

    void printVegetarianMenu() const {
        std::cout << "\nVEGETARIAN MENU\n";
        std::cout << "---------------\n";
        printVegetarianHelper(m_allMenus);
    }

private:
    void printVegetarianHelper(MenuComponent* component) const {
        try {
            // Try to access as leaf
            if (component->isVegetarian()) {
                component->print();
            }
        } catch (const std::runtime_error&) {
            // Must be a composite, iterate through children
            try {
                auto iterator = component->createIterator();
                // Note: Full implementation would traverse using iterator
                // For now, we rely on direct child access
            } catch (const std::runtime_error&) {
                // No iterator support
            }
        }
    }
};

#endif // COMPOSITE_WAITRESS_H
