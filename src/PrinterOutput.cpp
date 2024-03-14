#include "PrinterOutput.h"
#include "iostream"

string getQueueInfo(Device* &device) {
    string queueinfo;
    int jobsamount = device->getJobs().size();

    for (int i = 0; i < jobsamount ; ++i) {
        Job* currentjobinqueue = device->getJobs()[i];
        int  jobnummer = currentjobinqueue->getJobNumber();
        string userinqueue = currentjobinqueue->getUserName();

        queueinfo += "\t\t[#" + to_string(jobnummer) + "|" + userinqueue + "]";

        if(i != jobsamount-1){
            queueinfo += "\n";
        }
    }
    return queueinfo;
}

string getCurrentInfo(Device* &device){
    string currentinfo;

    Job* currentjob = device->getCurrentJob();
    int jobnummer = currentjob->getJobNumber();
    string user = currentjob->getUserName();
    currentinfo = "[#" + to_string(jobnummer) + "|" + user + "]";
    return currentinfo;
}

void writeDeviceInfo(System& system, std::ofstream& file) {
    auto& devices = system.getDevices();
    for (Device* device : devices) {
        file << device->getName() << " (CO2: " << device->getEmissions() << "g/page):" << endl;
        file << "\t* Current:" << endl << "\t\t"+ getCurrentInfo(device) << endl;
        file << "\t* Queue:" << endl;
        file << getQueueInfo(device) << endl;
    }
}

