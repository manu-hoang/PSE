#include "System.h"
#include "contracts/DesignByContract.h"

System::System() {
    _initCheck = this;

    _devices = {};
    _jobs = {};
    current_time = 0;

    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
    ENSURE(_devices.empty(), "Devices vector must be empty after initialization");
    ENSURE(_jobs.empty(), "Jobs vector must be empty after initialization");
    ENSURE(current_time == 0, "time must start at 0 after initialization");
}

bool System::properlyInitialized() {
    return _initCheck == this;
}

void System::automatic_run(int seconds) {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling automatic_run");
    REQUIRE(seconds >= 0, "Automatic run time must be a positive integer");

    update_all_devices();

    while (current_time <= seconds){

        process_all_jobs();
        update_all_devices();

        current_time++;
    }

}

void System::link_jobs() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling link_jobs");

    if(_devices.empty()){
        return;
    }

    REQUIRE(!_devices.empty(), "No device available to give jobs to");
    Device* device = _devices[0]; // change this later

    for(auto job : _jobs){
        device->add_job(job);
    }

    REQUIRE(current_time >= 0, "Current time must be a positive integer");
    device->update_current_job(current_time);
}

void System::update_all_devices() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling update_all_devices");

    for(auto device : _devices) {
        device->update_current_job(current_time);
    }
}


void System::process_all_jobs() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling process_all_jobs");

    for(auto device : _devices){

        if(!device->getBusy()){
            return;
        }
        ENSURE(device->getBusy(), "Device must have a current job to process");

        auto current_job = device->getCurrentJob();
        REQUIRE(current_job != nullptr, "Printing finish time must be greater than 0");

        // job finish time
        double finish_time = current_job->getStartTime() + device->get_printing_time();
        REQUIRE(finish_time >= 0, "Printing finish time must be greater than 0");

        if(current_time >= finish_time){
            while(!current_job->getFinished()) {
                device->print_page();
            }
            ENSURE(current_job->getFinished(), "current job must be finished after printing all pages");
        }

    }
}

void System::addDevice(Device* &device) {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling addDevice");
    REQUIRE(device != nullptr, "Cannot add nullptr as device to system");

    this->_devices.push_back(device);
}

void System::addJob(Job* &job) {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling addJob");
    REQUIRE(job != nullptr, "Cannot add nullptr as job to system");

    this->_jobs.push_back(job);
}

std::vector<Device*> &System::getDevices() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling getDevices");
    return _devices;
}

vector<Job*> &System::getJobs() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling getJobs");
    return _jobs;
}