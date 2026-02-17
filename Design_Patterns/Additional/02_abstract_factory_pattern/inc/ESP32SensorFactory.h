#ifndef ESP32_SENSOR_FACTORY_H
#define ESP32_SENSOR_FACTORY_H

#include "SensorFactory.h"
#include "ESP32TemperatureSensor.h"
#include "ESP32PressureSensor.h"
#include <iostream>

/**
 * @brief Concrete Factory: ESP32 Platform Sensor Factory
 *
 * Creates family of ESP32-specific sensors
 * All sensors use ESP32 peripherals and drivers
 */
class ESP32SensorFactory : public SensorFactory {
public:
    ESP32SensorFactory() {
        std::cout << "[ESP32Factory] Initializing ESP32 sensor platform\n";
    }

    std::unique_ptr<TemperatureSensor> createTemperatureSensor() const override {
        return std::make_unique<ESP32TemperatureSensor>();
    }

    std::unique_ptr<PressureSensor> createPressureSensor() const override {
        return std::make_unique<ESP32PressureSensor>();
    }
};

#endif // ESP32_SENSOR_FACTORY_H
