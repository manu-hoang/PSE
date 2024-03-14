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

void device_print_message(Device &device, Job *&job) {
    const string& printer_name = device.getName();

    int job_number = job->getJobNumber();
    const string& job_username = job->getUserName();
    int job_pagecount = job->getPageCount();

    cout << "Printer " << printer_name << " finished job:" << endl;
    cout << "Number: " << job_number << endl;
    cout << "Submitted by: " << job_username << endl;
    cout << job_pagecount << " pages" << endl << endl;
}

