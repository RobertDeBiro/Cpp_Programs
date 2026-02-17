#ifndef SENSOR_FACTORY_H
#define SENSOR_FACTORY_H

#include <memory>
#include "TemperatureSensor.h"
#include "PressureSensor.h"

/**
 * @brief Abstract Factory: Sensor Factory Interface
 *
 * Declares interface for creating families of related sensor objects
 * Each concrete factory creates sensors for a specific platform
 */
class SensorFactory {
public:
    virtual ~SensorFactory() = default;

    virtual std::unique_ptr<TemperatureSensor> createTemperatureSensor() const = 0;
    virtual std::unique_ptr<PressureSensor> createPressureSensor() const = 0;
};

#endif // SENSOR_FACTORY_H
