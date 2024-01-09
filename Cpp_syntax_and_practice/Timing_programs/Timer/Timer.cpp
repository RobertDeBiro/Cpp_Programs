#include <iostream>
#include <chrono> // std::chrono
#include "../Timer/Timer.hpp"

void Timer::reset()
{
    m_beg = Clock::now();
}

double Timer::elapsed() const
{
    // Calculate time that passed from the moment of Timer instantiation
    auto timePassed{ Clock::now() - m_beg };

    // Change the type of timePassed to 'Second'
    Second timePassedSecond{ std::chrono::duration_cast<Second>(timePassed) };
    
    // Retrieve the time that passed from the moment of 'Timer' instantiation, in seconds
    auto timePassedInSeconds{ timePassedSecond.count() };

    return timePassedInSeconds;
}
