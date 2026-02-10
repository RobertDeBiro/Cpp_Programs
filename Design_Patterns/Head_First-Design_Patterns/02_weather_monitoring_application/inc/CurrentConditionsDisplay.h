#ifndef CURRENTCONDITIONSDISPLAY_H
#define CURRENTCONDITIONSDISPLAY_H

#include "Observer.h"
#include "DisplayElement.h"
#include "Subject.h"
#include <iostream>

// Concrete Observer - displays current weather conditions
// Implements both Observer (to receive updates) and DisplayElement (to display data)
class CurrentConditionsDisplay : public Observer, public DisplayElement {
private:
    float temperature;
    float humidity;
    Subject* weatherData;  // Reference to subject for potential unregistration

public:
    // Constructor registers this observer with the subject
    explicit CurrentConditionsDisplay(Subject* weatherDataSubject)
        : temperature(0.0f), humidity(0.0f), weatherData(weatherDataSubject) {
        weatherData->registerObserver(this);
    }

    // Destructor automatically unregisters (RAII pattern)
    ~CurrentConditionsDisplay() {
        if (weatherData) {
            weatherData->removeObserver(this);
        }
    }

    // Called by subject when measurements change (push model)
    void update(float temp, float hum, float /* press */) override {
        temperature = temp;
        humidity = hum;
        display();
    }

    // Display current conditions
    void display() const override {
        std::cout << "Current conditions: " << temperature
                  << "F degrees and " << humidity << "% humidity\n";
    }
};

#endif // CURRENTCONDITIONSDISPLAY_H
