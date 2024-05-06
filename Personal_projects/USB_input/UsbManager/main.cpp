#include <thread>
#include <iostream>

#include "MediaManager.h"

int main()
{
    MediaManager& mm = MediaManager::GetInstance();
    if(!mm.init()) return -1;
    std::thread listenUsbWorker(&MediaManager::startListening, &mm);
    listenUsbWorker.detach();

    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "***************** Hello from main! *****************\n";
    }

    return 0;
}