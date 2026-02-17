#ifndef ARM_TEMPERATURE_SENSOR_H
#define ARM_TEMPERATURE_SENSOR_H

#include "TemperatureSensor.h"
#include <iostream>
#include <random>

/**
 * @brief Concrete Product: ARM Platform Temperature Sensor
 *
 * Temperature sensor implementation for ARM-based embedded systems
 * Uses ARM-specific I2C communication and registers
 */
class ARMTemperatureSensor : public TemperatureSensor {
public:
    ARMTemperatureSensor() {
        std::cout << "[ARM] Initializing LM75 temperature sensor (I2C address 0x48)\n";
    }

    double readTemperature() const override {
        // Simulate reading from ARM I2C peripheral
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(20.0, 25.0);
        return dis(gen);
    }

    std::string getModel() const override {
        return "ARM LM75 (I2C)";
    }

    void calibrate() override {
        std::cout << "[ARM] Calibrating temperature sensor using ARM registers\n";
    }
};

#endif // ARM_TEMPERATURE_SENSOR_H
