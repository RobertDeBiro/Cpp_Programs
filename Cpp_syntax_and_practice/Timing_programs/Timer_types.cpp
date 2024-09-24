/**
 * 1) now                               ==   time_point
 *    to_time_t (time_point)            ---> std::time_t
 *    std::localtime (std::time_t)      ---> std::tm
 *    std::put_time (std::tm)           ---> std::stringstream
 * 
 * 2) std::get_time (std::stringstream) ---> std::tm
 *    mktime (std::tm)                  ---> std::time_t
 *    from_time_t (std::time_t)         ---> time_point
 *    time_point                        ==   now
 */

#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip> // std::put_time

int main()
{
    std::cout << "*****************************************************\n";

    using Clock = std::chrono::system_clock;

    // Retrieve current time
    std::chrono::time_point<Clock> time_clock = Clock::now();

    // Convert the 'time_point' object to a 'time_t' object,
    // which is a type suitable for representing the system time as a simple integer
    std::time_t time_t = Clock::to_time_t(time_clock);
    std::cout << "Time = " << time_t << std::endl;

    // Convert the 'time_t' object into a 'std::tm' structure representing the local time
    // as years, months, days, hours...
    std::tm* time_tm = std::localtime(&time_t);

    // Convert 'std::tm' structure into string with format %Y-%m-%d %H:%M:%S:
    // - %Y - year
    // - %m - month
    // - %d - day
    // - %H - hours
    // - %M - minutes
    // - %S - seconds
    std::stringstream time_string;
    time_string << std::put_time(time_tm, "%Y-%m-%d %H:%M:%S");
    std::cout << time_string.str() << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}
