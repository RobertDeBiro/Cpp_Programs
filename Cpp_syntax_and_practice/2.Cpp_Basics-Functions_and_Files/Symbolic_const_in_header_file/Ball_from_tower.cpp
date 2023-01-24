// LearnCpp
// Fundamental Data Types
// Summary and quiz

#include <iostream>
#include "Constants.hpp"

double getTowerHeight()
{
    std::cout << "Enter the height of the tower in meters: ";
    double h{};
    std::cin >> h;

    return h;
}

double calculateBallHeight(const double h, int t)
{
    double distanceFallen{ gravity * t * t / 2 };
    double currentHeight{ h - distanceFallen };

    if (currentHeight < 0.0)
        return 0.0;

    return currentHeight;
}

int main()
{
    const double towerHeight{ getTowerHeight() };

    std::cout << "At 0 seconds, the ball is at height: " << calculateBallHeight(towerHeight, 0) << "\n";
    std::cout << "At 1 seconds, the ball is at height: " << calculateBallHeight(towerHeight, 1) << "\n";
    std::cout << "At 2 seconds, the ball is at height: " << calculateBallHeight(towerHeight, 2) << "\n";
    std::cout << "At 3 seconds, the ball is at height: " << calculateBallHeight(towerHeight, 3) << "\n";
    std::cout << "At 4 seconds, the ball is at height: " << calculateBallHeight(towerHeight, 4) << "\n";
    std::cout << "At 5 seconds, the ball is at height: " << calculateBallHeight(towerHeight, 5) << "\n";

    return 0;
}
