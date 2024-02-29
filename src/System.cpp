#include "System.h"
#include "iostream"

void System::addDevice(Device* &device) {
    this->_devices.push_back(device);
}

void System::addJob(Job* &job) {
    this->_jobs.push_back(job);
}

void print_message(Job* &job, Device* &printer){
    string printer_name = printer->getName();

    int job_number = job->getJobNumber();
    string job_username = job->getUserName();
    int job_pagecount = job->getPageCount();

    cout << "Printer " << printer_name << " finished job:" << endl;
    cout << "Number: " << job_number << endl;
    cout << "Submitted by: " << job_username << endl;
    cout << job_pagecount << " pages" << endl;
}

void System::process_job(Job* &job, Device* &printer) {
    job->process();

    print_message(job, printer);
}

const std::vector<Device *> &System::getDevices() const{
    return _devices;
}
