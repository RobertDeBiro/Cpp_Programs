#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <string>

/**
 * @brief Abstract Product: Temperature Sensor Interface
 *
 * Defines interface for temperature sensors across different platforms
 */
class TemperatureSensor {
public:
    virtual ~TemperatureSensor() = default;

    virtual double readTemperature() const = 0;
    virtual std::string getModel() const = 0;
    virtual void calibrate() = 0;
};

#endif // TEMPERATURE_SENSOR_H
