#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>

namespace fs = std::filesystem;

int main()
{
    std::cout << "*****************************************************\n";

    std::thread usbThread([]
    {
        // We can use append '/' operator within 'fs::path' only if one of operands is 'fs::path'
        fs::path mediaPath{fs::path("/media") / getenv("USERNAME")};

        // Infinitely iterate over the contents of the "/media/robert" directory
        while (true)
        {
            if (!fs::is_empty(mediaPath))
            {
                std::cout << "USB device detected!" << std::endl;
            }
            else
            {
                std::cout << "No USB device!" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    usbThread.join();

    std::cout << "*****************************************************\n";
    return 0;
}
