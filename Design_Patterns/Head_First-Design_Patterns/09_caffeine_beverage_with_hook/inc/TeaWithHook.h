#ifndef TEA_WITH_HOOK_H
#define TEA_WITH_HOOK_H

#include "CaffeineBeverageWithHook.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

/**
 * @brief Concrete implementation of CaffeineBeverageWithHook for tea
 *
 * This class provides tea-specific implementations for:
 * - Brewing: Steeping tea bag in water
 * - Condiments: Adding lemon
 * - Hook override: Asking user if they want condiments
 */
class TeaWithHook : public CaffeineBeverageWithHook {
protected:
    /**
     * @brief Implementation of abstract method: Brew tea
     *
     * Tea-specific brewing: steep the tea bag
     */
    void brew() override {
        std::cout << "Steeping the tea\n";
    }

    /**
     * @brief Implementation of abstract method: Add tea condiments
     *
     * Tea-specific condiments: lemon
     */
    void addCondiments() override {
        std::cout << "Adding Lemon\n";
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

        std::cout << "Would you like lemon with your tea (y/n)? ";

        if (!std::getline(std::cin, answer)) {
            std::cerr << "IO error trying to read your answer\n";
            return "n";
        }

        return answer;
    }
};

#endif // TEA_WITH_HOOK_H
