#include "System.h"
#include "iostream"

void System::automatic_run(int seconds) {

    while (time <= seconds){


        time++;
    }

}

Device* System::find_available_printer() {

    for (auto printer : this->_devices) {
        if(!printer->getBusy()){
            return printer;
        }
    }

    // if no !busy printers, return nullptr
    return nullptr;
}

void System::process_all_jobs() {

}

void System::addDevice(Device* &device) {
    this->_devices.push_back(device);
}

void System::addJob(Job* &job) {
    this->_jobs.push_back(job);
}

const std::vector<Device *> &System::getDevices() const{
    return _devices;
}
