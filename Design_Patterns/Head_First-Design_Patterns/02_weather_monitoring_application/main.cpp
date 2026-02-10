#include "WeatherData.h"
#include "CurrentConditionsDisplay.h"
#include <iostream>

int main() {
    // Create the subject (observable)
    WeatherData weatherData;

    // Create observer and register it with subject
    // Observer automatically registers in constructor
    CurrentConditionsDisplay currentDisplay(&weatherData);

    std::cout << "=== Weather Monitoring Station ===" << std::endl;
    std::cout << std::endl;

    // Simulate weather measurements changing
    std::cout << "--- Measurement Update 1 ---" << std::endl;
    weatherData.setMeasurements(80.0f, 65.0f, 30.4f);
    std::cout << std::endl;

    std::cout << "--- Measurement Update 2 ---" << std::endl;
    weatherData.setMeasurements(82.0f, 70.0f, 29.2f);
    std::cout << std::endl;

    std::cout << "--- Measurement Update 3 ---" << std::endl;
    weatherData.setMeasurements(78.0f, 90.0f, 29.2f);
    std::cout << std::endl;

    std::cout << "=== Demonstration Complete ===" << std::endl;

    // Observer automatically unregisters in destructor (RAII)
    return 0;
}
