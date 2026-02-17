#include "HardwareManager.h"
#include <thread>
#include <chrono>

/**
 * @brief Simulates a motor controller accessing hardware manager
 */
void motorControllerTask() {
    std::cout << "[MotorController] Starting task...\n";

    // Get singleton instance
    HardwareManager& hwManager = HardwareManager::getInstance();

    // Initialize I2C for motor controller
    hwManager.initializeI2C(1);
    hwManager.setGPIOMode(12, "OUTPUT");

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    hwManager.printStatus();
}

/**
 * @brief Simulates a sensor module accessing hardware manager
 */
void sensorModuleTask() {
    std::cout << "[SensorModule] Starting task...\n";

    // Get singleton instance (same instance as motor controller!)
    HardwareManager& hwManager = HardwareManager::getInstance();

    // Initialize SPI for sensors
    hwManager.initializeSPI(0);
    hwManager.setGPIOMode(18, "INPUT");

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    hwManager.printStatus();
}

/**
 * @brief Demonstrates the Singleton pattern
 */
int main() {
    std::cout << "========================================\n";
    std::cout << "  SINGLETON PATTERN - Robotics Example\n";
    std::cout << "========================================\n\n";

    std::cout << "=== DEMONSTRATION 1: Same Instance ===\n\n";

    // First access - triggers construction
    std::cout << "Getting first instance...\n";
    HardwareManager& hw1 = HardwareManager::getInstance();
    hw1.initializeI2C(0);

    // Second access - returns SAME instance (no construction)
    std::cout << "Getting second instance...\n";
    HardwareManager& hw2 = HardwareManager::getInstance();
    hw2.initializeSPI(1);

    // Verify same instance
    std::cout << "\nVerifying singleton property:\n";
    std::cout << "Instance 1 address: " << &hw1 << "\n";
    std::cout << "Instance 2 address: " << &hw2 << "\n";
    std::cout << "Same instance? " << (&hw1 == &hw2 ? "YES" : "NO") << "\n";

    hw1.printStatus();

    std::cout << "\n=== DEMONSTRATION 2: Thread Safety ===\n\n";
    std::cout << "Launching concurrent tasks...\n\n";

    // Create two threads accessing the singleton concurrently
    std::thread motorThread(motorControllerTask);
    std::thread sensorThread(sensorModuleTask);

    // Wait for both threads to complete
    motorThread.join();
    sensorThread.join();

    std::cout << "\n=== DEMONSTRATION 3: Global State ===\n\n";

    // All modifications from threads are visible
    HardwareManager::getInstance().printStatus();

    std::cout << "Pattern benefits demonstrated:\n";
    std::cout << "  ✓ Single instance guaranteed\n";
    std::cout << "  ✓ Thread-safe initialization\n";
    std::cout << "  ✓ Global point of access\n";
    std::cout << "  ✓ Shared state across modules\n";
    std::cout << "  ✓ Lazy initialization\n\n";

    std::cout << "Program ending (singleton will be destroyed)...\n";

    return 0;
}
