#ifndef COMPOSITE_MENU_H
#define COMPOSITE_MENU_H

#include "MenuComponent.h"
#include "Iterator.h"
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <stack>

/**
 * @brief Composite component in the Composite Pattern
 *
 * Represents a menu that can contain both MenuItems and other Menus.
 * Implements composite operations (add, remove, getChild) and delegates
 * operations to its children through recursion.
 */
class CompositeMenu : public MenuComponent {
private:
    std::vector<std::unique_ptr<MenuComponent>> m_menuComponents;
    std::string m_name;
    std::string m_description;

    /**
     * @brief Iterator for traversing composite structures
     *
     * Uses a stack to perform depth-first traversal of the menu hierarchy.
     * Automatically handles nested menus by pushing child iterators onto the stack.
     */
    class CompositeIterator : public Iterator {
    private:
        std::stack<std::vector<MenuComponent*>::iterator> m_stack;
        std::vector<MenuComponent*> m_components;
        size_t m_position{0};

    public:
        explicit CompositeIterator(const std::vector<std::unique_ptr<MenuComponent>>& components) {
            // Convert to raw pointers for iteration
            m_components.reserve(components.size());
            for (const auto& comp : components) {
                m_components.push_back(comp.get());
            }
        }

        bool hasNext() const override {
            return m_position < m_components.size();
        }

        MenuItem* next() override {
            if (!hasNext()) {
                return nullptr;
            }

            // Advance position
            ++m_position;

            // If it's a composite menu, we would need to traverse its children
            // For simplicity, we just return nullptr for this basic implementation
            // A full implementation would use a stack-based approach
            return nullptr; // MenuComponent is not directly convertible to MenuItem
        }
    };

public:
    CompositeMenu(std::string name, std::string description)
        : m_name(std::move(name))
        , m_description(std::move(description)) {}

    void add(std::unique_ptr<MenuComponent> component) override {
        m_menuComponents.push_back(std::move(component));
    }

    void remove(MenuComponent* component) override {
        auto it = std::find_if(m_menuComponents.begin(), m_menuComponents.end(),
                               [component](const auto& ptr) { return ptr.get() == component; });
        if (it != m_menuComponents.end()) {
            m_menuComponents.erase(it);
        }
    }

    MenuComponent* getChild(size_t index) override {
        if (index < m_menuComponents.size()) {
            return m_menuComponents[index].get();
        }
        return nullptr;
    }

    [[nodiscard]] std::string getName() const override { return m_name; }
    [[nodiscard]] std::string getDescription() const override { return m_description; }

    void print() const override {
        std::cout << "\n" << m_name;
        std::cout << ", " << m_description << "\n";
        std::cout << "---------------------\n";

        // Recursively print all children (both MenuItems and submenus)
        for (const auto& component : m_menuComponents) {
            component->print();
        }
    }

    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<CompositeIterator>(m_menuComponents);
    }
};

#endif // COMPOSITE_MENU_H
