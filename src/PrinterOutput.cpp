#include "PrinterOutput.h"
#include "contracts/DesignByContract.h"
#include "iostream"

string getCurrentInfo(Device* &device){
    REQUIRE(device->properlyInitialized(), "Device wasn't initialized when calling getCurrentInfo.");

    string currentinfo;

    Job* currentjob = device->getCurrentJob();
    int jobnummer = currentjob->getJobNumber();
    string user = currentjob->getUserName();
    currentinfo = "[#" + to_string(jobnummer) + "|" + user + "]";
    return currentinfo;
}

string getQueueInfo(Device* &device) {
    REQUIRE(device->properlyInitialized(), "Device wasn't initialized when calling getQueueInfo.");

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

void writeDeviceInfo(System& system) {
    REQUIRE(system.properlyInitialized(), "System wasn't initialized when calling writeDeviceInfo.");

    ofstream file("in_output/output.txt");
    auto& devices = system.getDevices();
    for (Device* device : devices) {
        file << device->getName() << " (CO2: " << device->getEmissions() << "g/page):" << endl;
        file << "\t* Current:" << endl << "\t\t"+ getCurrentInfo(device) << endl;
        file << "\t* Queue:" << endl;
        file << getQueueInfo(device) << endl;
    }
}

void device_print_message(Device &device, Job *&job) {
    REQUIRE(device.properlyInitialized(), "Device wasn't initialized when calling device_print_message.");
    REQUIRE(job->properlyInitialized(), "Job wasn't initialized when calling device_print_message.");

    const string& printer_name = device.getName();

    int job_number = job->getJobNumber();
    const string& job_username = job->getUserName();
    int job_pagecount = job->getTotalPageCount();

    cout << "Printer " << printer_name << " finished job:" << endl;
    cout << "\tNumber: " << job_number << endl;
    cout << "\tSubmitted by: " << job_username << endl;
    cout << "\t" << job_pagecount << " pages" << endl << endl;

/*    ofstream ConsoleOutputFile;
    ConsoleOutputFile.open("in_output/console_output.txt");

    ConsoleOutputFile << "Printer " << printer_name << " finished job:" << endl;
    ConsoleOutputFile << "\tNumber: " << job_number << endl;
    ConsoleOutputFile << "\tSubmitted by: " << job_username << endl;
    ConsoleOutputFile << "\t" << job_pagecount << " pages" << endl << endl;

    ConsoleOutputFile.close();*/
}

