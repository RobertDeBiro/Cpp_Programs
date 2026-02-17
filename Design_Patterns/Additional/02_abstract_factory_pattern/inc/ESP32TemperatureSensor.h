#ifndef ESP32_TEMPERATURE_SENSOR_H
#define ESP32_TEMPERATURE_SENSOR_H

#include "TemperatureSensor.h"
#include <iostream>
#include <random>

/**
 * @brief Concrete Product: ESP32 Platform Temperature Sensor
 *
 * Temperature sensor implementation for ESP32 embedded systems
 * Uses ESP32-specific I2C driver and ADC
 */
class ESP32TemperatureSensor : public TemperatureSensor {
public:
    ESP32TemperatureSensor() {
        std::cout << "[ESP32] Initializing DHT22 temperature sensor (GPIO 4)\n";
    }

    double readTemperature() const override {
        // Simulate reading from ESP32 GPIO/ADC
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(22.0, 27.0);
        return dis(gen);
    }

    std::string getModel() const override {
        return "ESP32 DHT22 (1-Wire)";
    }

    void calibrate() override {
        std::cout << "[ESP32] Calibrating temperature sensor using ESP32 ADC\n";
    }
};

#endif // ESP32_TEMPERATURE_SENSOR_H
