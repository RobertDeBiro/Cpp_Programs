#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include <string>

/**
 * @brief Abstract Product: Pressure Sensor Interface
 *
 * Defines interface for pressure sensors across different platforms
 */
class PressureSensor {
public:
    virtual ~PressureSensor() = default;

    virtual double readPressure() const = 0;
    virtual std::string getModel() const = 0;
    virtual void calibrate() = 0;
};

#endif // PRESSURE_SENSOR_H
