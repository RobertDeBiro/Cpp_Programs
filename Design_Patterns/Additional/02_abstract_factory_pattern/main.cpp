#include "ARMSensorFactory.h"
#include "ESP32SensorFactory.h"
#include "WeatherStation.h"
#include <iostream>
#include <memory>

/**
 * @brief Demonstrates Abstract Factory Pattern with embedded sensor platforms
 */
int main() {
    std::cout << "========================================\n";
    std::cout << " ABSTRACT FACTORY PATTERN\n";
    std::cout << " Embedded Sensor Platforms\n";
    std::cout << "========================================\n\n";

    // ====================================================================
    // DEMONSTRATION 1: ARM Platform
    // ====================================================================
    std::cout << "=== DEMONSTRATION 1: ARM Platform ===\n\n";

    ARMSensorFactory armFactory;
    WeatherStation armStation(armFactory);

    armStation.displayReadings();
    armStation.calibrateSensors();

    // ====================================================================
    // DEMONSTRATION 2: ESP32 Platform
    // ====================================================================
    std::cout << "=== DEMONSTRATION 2: ESP32 Platform ===\n\n";

    ESP32SensorFactory esp32Factory;
    WeatherStation esp32Station(esp32Factory);

    esp32Station.displayReadings();
    esp32Station.calibrateSensors();

    // ====================================================================
    // DEMONSTRATION 3: Runtime Platform Selection
    // ====================================================================
    std::cout << "=== DEMONSTRATION 3: Runtime Platform Selection ===\n\n";

    // Simulate runtime platform detection
    bool isARM = true;  // Could be detected at runtime

    std::cout << "Detected platform: " << (isARM ? "ARM" : "ESP32") << "\n\n";

    std::unique_ptr<SensorFactory> factory;
    if (isARM) {
        factory = std::make_unique<ARMSensorFactory>();
    } else {
        factory = std::make_unique<ESP32SensorFactory>();
    }

    WeatherStation runtimeStation(*factory);
    runtimeStation.displayReadings();

    // ====================================================================
    // Pattern Benefits
    // ====================================================================
    std::cout << "=== Pattern Benefits Demonstrated ===\n\n";
    std::cout << "✓ Platform Independence:\n";
    std::cout << "  WeatherStation works with ANY platform\n";
    std::cout << "  without knowing platform details\n\n";

    std::cout << "✓ Family Consistency:\n";
    std::cout << "  All sensors from same platform (no mixing)\n";
    std::cout << "  ARM factory creates only ARM sensors\n";
    std::cout << "  ESP32 factory creates only ESP32 sensors\n\n";

    std::cout << "✓ Easy to Extend:\n";
    std::cout << "  Add new platform: Create new factory\n";
    std::cout << "  Add new sensor type: Add to all factories\n";
    std::cout << "  Client code unchanged!\n\n";

    std::cout << "✓ Compile-Time Safety:\n";
    std::cout << "  Can't accidentally mix ARM and ESP32 sensors\n";
    std::cout << "  Type system enforces consistency\n\n";

    std::cout << "✓ Dependency Inversion:\n";
    std::cout << "  Client depends on abstractions (interfaces)\n";
    std::cout << "  not concrete implementations\n\n";

    return 0;
}
