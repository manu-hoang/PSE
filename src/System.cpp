#include "System.h"
#include "iostream"

void System::automatic_run(int seconds) {

}

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

Device *System::find_available_printer() {

    for (auto printer : this->_devices) {
        if(!printer->getBusy()){
            return printer;
        }
    }

    // if no !busy printers, return nullptr
    return nullptr;
}


bool System::process_job(Job* &job) {

    if(job->getFinished()){
        cout << "alr finished" << endl;
        return false;
    }

    Device* printer = find_available_printer();

    if(printer == nullptr){
        return false;
    }

    job->process();
    print_message(job, printer);
    return true;
}

void System::process_all_jobs() {
    for (auto job : this->_jobs){
        process_job(job);
    }
}

const std::vector<Device *> &System::getDevices() const{
    return _devices;
}
