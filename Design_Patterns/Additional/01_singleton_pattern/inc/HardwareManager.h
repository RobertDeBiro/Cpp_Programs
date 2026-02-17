#ifndef HARDWARE_MANAGER_H
#define HARDWARE_MANAGER_H

#include <iostream>
#include <string>
#include <mutex>
#include <vector>
#include <memory>

/**
 * @brief Singleton Hardware Manager for robotics system
 *
 * Manages exclusive access to hardware resources (I2C bus, SPI, GPIO, etc.)
 * Must have exactly ONE instance to prevent:
 * - Resource conflicts (multiple threads accessing same hardware)
 * - Initialization overhead (expensive hardware setup)
 * - State inconsistency (different parts of code with different hardware views)
 *
 * Implementation: Meyer's Singleton (C++11 thread-safe static initialization)
 */
class HardwareManager {
public:
    // Delete copy constructor and assignment operator
    HardwareManager(const HardwareManager&) = delete;
    HardwareManager& operator=(const HardwareManager&) = delete;

    /**
     * @brief Get the singleton instance (thread-safe)
     * @return Reference to the singleton instance
     *
     * Meyer's Singleton: C++11 guarantees thread-safe initialization
     * of static local variables
     */
    static HardwareManager& getInstance() {
        static HardwareManager instance;
        return instance;
    }

    // Hardware operations (simplified for demonstration)

    void initializeI2C(uint8_t bus) {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "[HardwareManager] Initializing I2C bus "
                  << static_cast<int>(bus) << "\n";
        m_i2cBuses.push_back(bus);
    }

    void initializeSPI(uint8_t device) {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "[HardwareManager] Initializing SPI device "
                  << static_cast<int>(device) << "\n";
        m_spiDevices.push_back(device);
    }

    void setGPIOMode(uint8_t pin, const std::string& mode) {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "[HardwareManager] Setting GPIO pin "
                  << static_cast<int>(pin) << " to mode: " << mode << "\n";
    }

    void printStatus() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << "\n=== Hardware Manager Status ===\n";
        std::cout << "Instance Address: " << this << "\n";
        std::cout << "I2C Buses: " << m_i2cBuses.size() << "\n";
        std::cout << "SPI Devices: " << m_spiDevices.size() << "\n";
        std::cout << "==============================\n\n";
    }

private:
    /**
     * @brief Private constructor (Singleton pattern)
     *
     * Expensive hardware initialization happens only once
     */
    HardwareManager() {
        std::cout << "[HardwareManager] CONSTRUCTING singleton instance at "
                  << this << "\n";
        std::cout << "[HardwareManager] Performing expensive hardware initialization...\n";
        // Simulate expensive initialization
        std::cout << "[HardwareManager] Initialization complete!\n\n";
    }

    /**
     * @brief Destructor (cleanup hardware resources)
     */
    ~HardwareManager() {
        std::cout << "\n[HardwareManager] DESTROYING singleton instance\n";
        std::cout << "[HardwareManager] Cleaning up hardware resources...\n";
    }

    // Hardware state
    std::vector<uint8_t> m_i2cBuses;
    std::vector<uint8_t> m_spiDevices;
    mutable std::mutex m_mutex;  // Thread-safe access
};

#endif // HARDWARE_MANAGER_H
