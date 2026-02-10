#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include "Subject.h"
#include "Observer.h"
#include <vector>
#include <algorithm>

// Concrete Subject - WeatherData maintains weather measurements
// and notifies all registered observers when measurements change
class WeatherData : public Subject {
private:
    std::vector<Observer*> observers;
    float temperature;
    float humidity;
    float pressure;

public:
    WeatherData() : temperature(0.0f), humidity(0.0f), pressure(0.0f) {}

    // Register an observer to receive updates
    void registerObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    // Remove an observer from the notification list
    void removeObserver(Observer* observer) override {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    // Notify all registered observers of state change
    void notifyObservers() override {
        for (Observer* observer : observers) {
            observer->update(temperature, humidity, pressure);
        }
    }

    // Called when measurements are updated
    void measurementsChanged() {
        notifyObservers();
    }

    // Set new measurements and trigger notifications
    void setMeasurements(float temp, float hum, float press) {
        temperature = temp;
        humidity = hum;
        pressure = press;
        measurementsChanged();
    }

    // Getters for pull-based updates (if needed)
    float getTemperature() const { return temperature; }
    float getHumidity() const { return humidity; }
    float getPressure() const { return pressure; }
};

#endif // WEATHERDATA_H
