#ifndef ARM_PRESSURE_SENSOR_H
#define ARM_PRESSURE_SENSOR_H

#include "PressureSensor.h"
#include <iostream>
#include <random>

/**
 * @brief Concrete Product: ARM Platform Pressure Sensor
 *
 * Pressure sensor implementation for ARM-based embedded systems
 * Uses ARM-specific SPI communication
 */
class ARMPressureSensor : public PressureSensor {
public:
    ARMPressureSensor() {
        std::cout << "[ARM] Initializing BMP280 pressure sensor (SPI CS=0)\n";
    }

    double readPressure() const override {
        // Simulate reading from ARM SPI peripheral
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(1010.0, 1015.0);
        return dis(gen);
    }

    std::string getModel() const override {
        return "ARM BMP280 (SPI)";
    }

    void calibrate() override {
        std::cout << "[ARM] Calibrating pressure sensor using ARM SPI\n";
    }
};

#endif // ARM_PRESSURE_SENSOR_H
