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

void writeDeviceInfo(System& system) {
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
    const string& printer_name = device.getName();
    const string filename = "in_output/console_output.txt";

    int job_number = job->getJobNumber();
    const string& job_username = job->getUserName();
    int job_pagecount = job->getTotalPageCount();

    cout << "Printer " << printer_name << " finished job:" << endl;
    cout << "\tNumber: " << job_number << endl;
    cout << "\tSubmitted by: " << job_username << endl;
    cout << "\t" << job_pagecount << " pages" << endl << endl;

    static bool first_write = true;

    ofstream file;
    if (first_write) {
        file.open(filename, ios::out);
        first_write = false;
    } else {
        file.open(filename, ios::app);
    }

    file << "Printer " << printer_name << " finished job:" << endl;
    file << "\tNumber: " << job_number << endl;
    file << "\tSubmitted by: " << job_username << endl;
    file << "\t" << job_pagecount << " pages" << endl << endl;

}

