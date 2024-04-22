#include "System.h"
#include "contracts/DesignByContract.h"
#include <iostream>

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

// Auxiliary function for internal use only

bool unfinished_jobs(System* system) {
    bool unfinished = false;

    for (auto job : system->getJobs()) {
        if(!job->getFinished()){
            unfinished = true;
        }
    }

    return unfinished;
}

// Auxiliary function for internal use only

Job* pick_job(System* system){

    for(auto job : system->getJobs()){
        if(!job->get_busy()){
            job->set_busy(true);
            return job;
        }
    }

    return nullptr;
}

Device* pick_device(System* system, Job* job){
    Device* return_device = nullptr;

    JobEnum job_type = job->get_type();
    DeviceEnum LF_device_type = invalid_device; // LF = Looking For

    switch (job_type) {
        case bw_job:
            LF_device_type = bw_device;
            break;

        case color_job:
            LF_device_type = color_device;
            break;

        case scan_job:
            LF_device_type = scan_device;
            break;

        case invalid_job:
            LF_device_type = invalid_device;
            break;
    }

    // TODO: change this later
    for(auto device : system->getDevices()){

        if(device->get_type() == LF_device_type){
            return_device = device;
        }
    }

    ENSURE(return_device != nullptr ,"No device exists for the specified job type");

    return return_device;
}

void System::automated_processing() {
    /*
    1. WHILE unfinished jobs left
        1.1. Pick job
        1.2. Choose device according to job type
        1.3. Perform Use Case 3.3: Manual processing met type (new)
    */

    while(unfinished_jobs(this)){
        // pick job
        Job* job = pick_job(this);

        // choose device
        Device* appropiate_device = pick_device(this, job);

        appropiate_device->add_job(job);

        // perform manual processing
        manual_processing(appropiate_device);
    }

}

void System::manual_processing(Device* device) {

    Job* job = device->getCurrentJob();

    JobEnum type = job->get_type();

    while(!job->getFinished()){
        switch (type) {
            case bw_job:
                job->print_page();
                break;

            case color_job:
                job->print_page();
                break;

            case scan_job:
                job->print_page();
                break;

            case invalid_job:
                return;
        }
    }

    device->writeOn(cout);
}
