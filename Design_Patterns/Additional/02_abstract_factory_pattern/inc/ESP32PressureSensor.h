#ifndef ESP32_PRESSURE_SENSOR_H
#define ESP32_PRESSURE_SENSOR_H

#include "PressureSensor.h"
#include <iostream>
#include <random>

/**
 * @brief Concrete Product: ESP32 Platform Pressure Sensor
 *
 * Pressure sensor implementation for ESP32 embedded systems
 * Uses ESP32-specific I2C driver
 */
class ESP32PressureSensor : public PressureSensor {
public:
    ESP32PressureSensor() {
        std::cout << "[ESP32] Initializing BME280 pressure sensor (I2C address 0x76)\n";
    }

    double readPressure() const override {
        // Simulate reading from ESP32 I2C peripheral
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(1008.0, 1013.0);
        return dis(gen);
    }

    std::string getModel() const override {
        return "ESP32 BME280 (I2C)";
    }

    void calibrate() override {
        std::cout << "[ESP32] Calibrating pressure sensor using ESP32 I2C driver\n";
    }
};

#endif // ESP32_PRESSURE_SENSOR_H
