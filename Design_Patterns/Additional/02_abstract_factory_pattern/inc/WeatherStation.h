#ifndef WEATHER_STATION_H
#define WEATHER_STATION_H

#include "SensorFactory.h"
#include <iostream>
#include <iomanip>
#include <memory>

/**
 * @brief Client: Weather Station
 *
 * Platform-independent weather station that works with any sensor factory
 * Doesn't know about specific platforms (ARM, ESP32)
 * Only depends on abstract interfaces
 */
class WeatherStation {
public:
    explicit WeatherStation(const SensorFactory& factory)
        : m_temperatureSensor(factory.createTemperatureSensor()),
          m_pressureSensor(factory.createPressureSensor()) {
        std::cout << "[WeatherStation] Initialized with sensor family\n\n";
    }

    void displayReadings() const {
        std::cout << "=== Weather Station Readings ===\n";
        std::cout << std::fixed << std::setprecision(1);

        std::cout << "Temperature Sensor: " << m_temperatureSensor->getModel() << "\n";
        std::cout << "  Current: " << m_temperatureSensor->readTemperature() << "°C\n";

        std::cout << "Pressure Sensor: " << m_pressureSensor->getModel() << "\n";
        std::cout << "  Current: " << m_pressureSensor->readPressure() << " hPa\n";

        std::cout << "================================\n\n";
    }

    void calibrateSensors() {
        std::cout << "Calibrating all sensors...\n";
        m_temperatureSensor->calibrate();
        m_pressureSensor->calibrate();
        std::cout << "Calibration complete!\n\n";
    }

private:
    std::unique_ptr<TemperatureSensor> m_temperatureSensor;
    std::unique_ptr<PressureSensor> m_pressureSensor;
};

#endif // WEATHER_STATION_H
