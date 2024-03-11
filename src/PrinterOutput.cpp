#include "PrinterOutput.h"
#include "iostream"

void writeDeviceInfo(const System& system, std::ofstream& file) {
    const auto& devices = system.getDevices();
    for (const auto& device : devices) {
        file << device->getName() << " (CO2: " << device->getEmissions() << "g/page):" << endl;
        file << "\t* Current:" << endl << "\t\t"+device->getCurrentInfo() << endl;
        file << "\t* Queue:" << endl;
        file << device->getQueueInfo() << endl;
    }
}

