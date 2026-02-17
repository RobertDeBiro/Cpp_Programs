#ifndef ARM_SENSOR_FACTORY_H
#define ARM_SENSOR_FACTORY_H

#include "SensorFactory.h"
#include "ARMTemperatureSensor.h"
#include "ARMPressureSensor.h"
#include <iostream>

/**
 * @brief Concrete Factory: ARM Platform Sensor Factory
 *
 * Creates family of ARM-specific sensors
 * All sensors use ARM peripherals (I2C, SPI, etc.)
 */
class ARMSensorFactory : public SensorFactory {
public:
    ARMSensorFactory() {
        std::cout << "[ARMFactory] Initializing ARM sensor platform\n";
    }

    std::unique_ptr<TemperatureSensor> createTemperatureSensor() const override {
        return std::make_unique<ARMTemperatureSensor>();
    }

    std::unique_ptr<PressureSensor> createPressureSensor() const override {
        return std::make_unique<ARMPressureSensor>();
    }
};

#endif // ARM_SENSOR_FACTORY_H
