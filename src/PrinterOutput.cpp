#include "System.h"
#include <fstream>
#include <sstream>

void writeDeviceInfo(const System& system, std::ofstream& file) {
    const auto& devices = system.getDevices();
    for (const auto& device : devices) {
        file << device->getName() << " (CO2: " << device->getEmissions() << "g/page):" << endl;
        file << "* Current:" << endl << device->getCurrentInfo() << endl;
        file << "* Queue:" << endl << device->getQueueInfo() << endl;
    }
}

