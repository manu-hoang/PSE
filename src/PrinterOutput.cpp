#include "System.h"
#include <fstream>


#include "System.h"
#include <fstream>

void writeDeviceInfo(const System& system, std::ofstream& file) {
    const auto& devices = system._devices);

    for (const auto& device : devices) {
        file << "NEW-Printer (CO2: " << device->getEmissions() << "g/page):\n";
        file << "* Current:\n";
        for (const auto& job : device->getCurrentJobs()) {
            file << "[#" << job->getJobNumber() << "|" << job->getUserName() << "]\n";
        }
        file << "* Queue:\n";
        for (const auto& job : device->getQueueJobs()) {
            file << "[#" << job->getJobNumber() << "|" << job->getUserName() << "]\n";
        }
        file << "\n";
    }
}
