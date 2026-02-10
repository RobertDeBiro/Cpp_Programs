#ifndef COFFEE_WITH_HOOK_H
#define COFFEE_WITH_HOOK_H

#include "CaffeineBeverageWithHook.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

/**
 * @brief Concrete implementation of CaffeineBeverageWithHook for coffee
 *
 * This class provides coffee-specific implementations for:
 * - Brewing: Dripping coffee through a filter
 * - Condiments: Adding sugar and milk
 * - Hook override: Asking user if they want condiments
 */
class CoffeeWithHook : public CaffeineBeverageWithHook {
protected:
    /**
     * @brief Implementation of abstract method: Brew coffee
     *
     * Coffee-specific brewing: drip through filter
     */
    void brew() override {
        std::cout << "Dripping Coffee through filter\n";
    }

    /**
     * @brief Implementation of abstract method: Add coffee condiments
     *
     * Coffee-specific condiments: sugar and milk
     */
    void addCondiments() override {
        std::cout << "Adding Sugar and Milk\n";
    }

    /**
     * @brief Hook override: Ask user if they want condiments
     *
     * This demonstrates the power of hooks - subclasses can customize
     * the algorithm behavior without changing the algorithm structure.
     *
     * @return true if user answers 'y' or 'Y', false otherwise
     */
    bool customerWantsCondiments() override {
        std::string answer = getUserInput();

        if (answer.empty()) {
            return false;
        }

        // Convert to lowercase for comparison
        char firstChar = static_cast<char>(std::tolower(static_cast<unsigned char>(answer[0])));
        return firstChar == 'y';
    }

private:
    /**
     * @brief Get user input for condiment preference
     *
     * Prompts the user and reads their response.
     * Returns "n" if input fails (default to no condiments).
     *
     * @return User's answer as string
     */
    std::string getUserInput() const {
        std::string answer;

        std::cout << "Would you like milk and sugar with your coffee (y/n)? ";

        if (!std::getline(std::cin, answer)) {
            std::cerr << "IO error trying to read your answer\n";
            return "n";
        }

        return answer;
    }
};

#endif // COFFEE_WITH_HOOK_H
