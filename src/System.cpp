#include "System.h"
#include "contracts/DesignByContract.h"
#include <iostream>
#include <limits>

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
        if(!job->get_busy()){
            job->set_busy(true);
            return job;
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

        /*if(device->get_type() == type){
            int value_dev = 0;
            value_dev += calculate_total_pages(device);
            value_dev = value_dev * device->get_emissions();

            cout << calculate_total_pages(device) << " " << value_dev << endl;

            bool exceeded_limit = exceeded_CO2_limit(device, value_dev);

            if(!exceeded_limit && value_dev <= minimal_CO2){
                device->set_CO2(value_dev);
                minimal_CO2 = value_dev;
                return_device = device;
            }
        }*/

        if(device->get_type() == type){
            int pages = calculate_total_pages(device);

            if(pages < least_pages){
                least_pages = pages;
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

/*
    Note:   the code given below will always find the device with the least amount of pages
                [1.2] IF there exists more than one device of the required type -> IF there exists any device of the required type

        [1.2] IF more than one device of the required type:
        [1.2.a] THEN:
            [1.2.a.1] FOR each device dev that does not exceed the CO2-limit:
                [1.2.a.1.a] value(dev) += pages left in active job + pages in queue
                [1.2.a.1.b] value(dev) = value(dev) * CO2 per page
            [1.2.a.2] Choose the device with minimal value(dev) and that does not exceed the CO2-limit.
            [1.2.a.3] Perform Use Case 3.3: Manual processing met type (new)

        [1.2.b] ELSE:
            [1.2.b.1] Choose the unique device of the required type that does not exceed the CO2-limit.
            [1.2.b.2] Perform Use Case 3.3: Manual processing met type (new)
*/

    // Iterate through the system and find how many devices match the given type
    int counter = device_type_counter(system, LF_device_type);

    if (counter == 0){return_device = nullptr;} // no device found
    else{
        return_device = find_device(system, LF_device_type);
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

    cout << "YO THERE IS A BUG HERE" << endl;
    device->writeOn(cout);
}

void System::process_for(int seconds) {

}