#include "System.h"
#include <fstream>

#include "System.h"
#include <fstream>
#include <sstream>

void writeDeviceInfo(const System& system, std::ofstream& file) {
    const auto& devices = system.getDevices();
    for (const auto& device : devices) {
        std::stringstream deviceInfo;
        deviceInfo << device->getName() << " (CO2: " << device->getEmissions() << "g/page):" << endl;
        deviceInfo << "* Current:" << endl << device->getCurrentInfo() << endl;
        deviceInfo << "* Queue:" << endl << device->getQueueInfo() << endl;
        file << deviceInfo.str();
    }
}

