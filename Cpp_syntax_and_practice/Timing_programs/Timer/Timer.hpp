/*
 * References:
 *  - chrono: https://en.cppreference.com/w/cpp/header/chrono
 *  - duration: https://en.cppreference.com/w/cpp/chrono/duration
 *  - steady_clock: https://en.cppreference.com/w/cpp/chrono/steady_clock
 *  - time_point: https://en.cppreference.com/w/cpp/chrono/time_point
 *  - duration_cast: https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
 */

#include <iostream>
#include <chrono> // std::chrono

class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double, std::ratio<1>>;

    // Define variable that will monitor time
    //  - std::chrono::time_point
    //      - data type for monitoring the time
    //  - Clock
    //      - type of clock used for time count
    //  - Clock::now
    //      - returns a time_point representing the current value of the clock
	std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
	void reset();
	double elapsed() const;
};
