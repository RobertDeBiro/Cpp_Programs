/*
 * LearnCpp
 * Basic Object-oriented Programming
 * Timing your code
 */

#include <iostream>
#include <chrono> // for std::chrono functions
#include <typeinfo> // typeid

class Timer
{
private:
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double, std::ratio<1>>;

	std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
	void reset()
	{
		m_beg = Clock::now();
	}

	double elapsed() const
	{
        auto timePassed{ Clock::now() - m_beg };

        // Check data types
        //  - 'Clock::now()' and 'm_beg' data types differs from 'Clock::now() - m_beg' data type
        std::cout << "Data type = " << typeid(Clock::now()).name() << std::endl;
        std::cout << "Data type = " << typeid(m_beg).name() << std::endl;
        std::cout << "Data type = " << typeid(timePassed).name() << std::endl;

        std::cout << "-----------------------------------------------------\n";

        // Get the value of passed seconds, with 's' suffix representing seconds
        Second timePassedSecond{ std::chrono::duration_cast<Second>(timePassed) };

        // Get only the value of passed seconds, without the 's' suffix
        auto timePassedInSeconds{ timePassedSecond.count() };

        std::cout << "timePassed = " << timePassed << "\n";
        std::cout << "timePassedSecond = " << timePassedSecond << "\n";
        std::cout << "timePassedInSeconds = " << timePassedInSeconds << "\n";

        return timePassedInSeconds;
	}
};

int main()
{
    std::cout << "*****************************************************\n";

    // When object 't' is instantiated, it's member variable 'm_beg' is set to the time of instantiation
    Timer t;

    /*
     * Code to time should go here
     */

    double timeElapsed{ t.elapsed() };
    std::cout << "Time elapsed: " << timeElapsed << " seconds\n";

    std::cout << "*****************************************************\n";
    return 0;
}
