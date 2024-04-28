#include "System.h"
#include "contracts/DesignByContract.h"
#include <iostream>
#include <limits>

System::System() {
    _initCheck = this;

    _devices = {};
    _jobs = {};
    current_time = 0;

    totalCO2emission = 0;

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

void System::addCompensation(Compensation *compensation) {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling addCompensation");
    REQUIRE(compensation != nullptr, "Cannot add nullptr as compensation to system");

    this->_compensations.push_back(compensation);
}

std::vector<Device*> &System::getDevices() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling getDevices");
    return _devices;
}

vector<Job*> &System::getJobs() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling getJobs");
    return _jobs;
}

vector<Compensation*> System::getCompensations() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling getCompensations");
    return _compensations;
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
        if(!job->getFinished()){
            if(!job->get_busy()){
                job->set_busy(true);
                return job;
            }
        }
    }

    // no more jobs left to process
    return nullptr;
}

// Auxiliary function for internal use only

int device_type_counter(System* system, DeviceEnum type){

    int counter = 0;

    for(auto device : system->getDevices()){
        if(device->get_type() == type){
            counter++;
        }
    }

    return counter;
}

// Auxiliary function for internal use only

int calculate_total_pages(Device* device){
    int total_pages = 0;

    queue<Job*> temp_queue = device->get_queue();

    while (!temp_queue.empty()) {
        Job* job = temp_queue.front();
        total_pages += job->getCurrentPageCount();
        temp_queue.pop();
    }

    return total_pages;
}

// Auxiliary function for internal use only

bool exceeded_CO2_limit(Device* device, int value_dev){
    int new_value = value_dev + device->get_CO2();

    if(new_value > device->get_limit()){
        return true;
    }
    else{return false;}
}

// Auxiliary function for internal use only

Device* find_device(System* system, DeviceEnum type){

    Device* return_device = nullptr;
    int least_pages = numeric_limits<int>::max();

    for(auto device : system->getDevices()){

        if(device->get_type() == type){
            int pages = calculate_total_pages(device); // total pages of device

            int value_dev = pages;
            value_dev *= device->get_emissions();

            int new_CO2_value = device->get_CO2() + value_dev;

            bool exceeds_limit = device->exceeds_CO2_limit(new_CO2_value);

            if(pages < least_pages && !exceeds_limit){
                least_pages = pages;
                device->set_CO2(new_CO2_value);
                return_device = device;
            }
        }
    }

    if(return_device == nullptr){
        cout << "all devices exceed limit" << endl;
    }

    return return_device;
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

    return_device = find_device(system, LF_device_type);

    ENSURE(return_device != nullptr ,"No device exists for the specified job type");

    return return_device;
}

// Auxiliary function for internal use only

bool find_compensation(System* system, Job* job){
    for(auto compensation : system->getCompensations()){
        if(job->getCompNumber() == compensation->getCompNumber()){
            job->setCompensationName(compensation->getName());
            job->setCompensated(true);
            return true;
        }
    }
    return false;
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

        find_compensation(this, job);

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
                job->printFullPage();
                break;

            case color_job:
                job->printFullPage();
                break;

            case scan_job:
                job->printFullPage();
                break;

            case invalid_job:
                return;
        }

        if(!job->getCompensated()){this->totalCO2emission += device->get_emissions();}
    }

    device->popQueue();
    device->updatePositions(0);

    cout << "Printer \"" << device->getName() << "\" finished " << job->getType() << " job:" << endl;
    cout << "   Number: " << job->getJobNumber() << endl;
    cout << "   Submitted by \"" << job->getUserName() << "\"" << endl;
    cout << "   " << job->getTotalPageCount() << " pages" << endl;

    if(job->getCompensated()){
        cout << "Job " << job->getJobNumber() << " was made CO2 neutral with the support of \"" << job->getCompensationName() << "\"." << endl;
    }

    cout << endl;
}

void System::divideJobs() {
    for(auto job: _jobs){
        // choose device
        Device* appropiate_device = pick_device(this, job);

        appropiate_device->add_job(job);

        find_compensation(this, job);
    }
}

void System::tick() {
    for (auto device : _devices) {
        device->print(current_time);
    }

    current_time++;
}

void System::calculateStatistics() {

}
