/*
 * References:
 *  - 'std::chrono'
 *     - https://en.cppreference.com/w/cpp/header/chrono
 * 
 *  - 'std::chrono::steady_clock'
 *     - monotonic clock - it moves forward at a constant rate and is not subject to adjustments
 *     - it provides a high resolution compared to other clocks
 *     - suitable for measuring elapsed time, intervals, and durations
 *     - https://en.cppreference.com/w/cpp/chrono/steady_clock
 * 
 *  - 'std::chrono::steady_clock::now'
 *     - returns a time point representing the current point in time
 *     - https://en.cppreference.com/w/cpp/chrono/steady_clock/now
 * 
 *  - 'std::chrono::duration<class Rep, class Period>'
 *     - represents a time duration
 *     - the duration is expressed as a count of ticks of the tick period
 *     - if we want result in seconds, but we also except fractions of seconds, we use 'Rep' as 'double'
 *     - if we want results in specific time scale, we can use specific duration data types:
 *        - 'std::chrono::nanoseconds'
 *        - 'std::chrono::microseconds'
 *        - 'std::chrono::miliseconds'
 *        - 'std::chrono::seconds'
 *        - 'std::chrono::minutes'
 *        - 'std::chrono::hours'
 *     - https://en.cppreference.com/w/cpp/chrono/duration
 * 
 *  - 'std::time_point'
 *     - https://en.cppreference.com/w/cpp/chrono/time_point
 * 
 *  - 'std::duration_cast'
 *     - https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
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
    //  - 'std::chrono::time_point'
    //      - data type for monitoring the time
    //  - 'Clock'
    //      - type of clock used for time count
    //  - 'Clock::now'
    //      - returns a 'time_point' representing the current value of the clock
	std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
	void reset();
	double elapsed() const;
};
