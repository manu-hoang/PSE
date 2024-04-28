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
    totalOperatingCosts = 0;
    averageCO2perPage = 0;

    mostUsedCompensation = nullptr;
    mostUsedDevice = nullptr;

    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
    ENSURE(_devices.empty(), "Devices vector must be empty after initialization");
    ENSURE(_jobs.empty(), "Jobs vector must be empty after initialization");
    ENSURE(current_time == 0, "time must start at 0 after initialization");
}

bool System::properlyInitialized() {
    return _initCheck == this;
}

void System::addDevice(Device* device) {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling addDevice");
    REQUIRE(device != nullptr, "Cannot add nullptr as device to system");

    this->_devices.push_back(device);
}

void System::addJob(Job* job) {
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

vector<Job*> System::getJobs() {
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
        // all devices exceed limit
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

    job->setTotalCO2(job->getTotalPageCount() * return_device->get_emissions());
    job->setTotalCost(job->getTotalPageCount() * return_device->getCosts());

    return return_device;
}

bool System::find_compensation(Job *job) {

    for(auto compensation : this->getCompensations()){
        if(job->getCompNumber() == compensation->getCompNumber()){
            job->setCompensationName(compensation->getName());
            job->setCompensated(true);
            compensation->increaseCount();
            return true;
        }
    }
    return false;
}

void System::automated_processing(std::ostream& onStream) {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling automated_processing");


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

        find_compensation(job);

        // perform manual processing
        manual_processing(onStream, appropiate_device);
    }

}

void System::manual_processing(std::ostream& onStream, Device* device) {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling manual_processing");

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

    onStream << "Printer \"" << device->getName() << "\" finished " << job->getType() << " job:" << endl;
    onStream << "   Number: " << job->getJobNumber() << endl;
    onStream << "   Submitted by \"" << job->getUserName() << "\"" << endl;
    onStream << "   " << job->getTotalPageCount() << " pages" << endl;

    if(job->getCompensated()){
        onStream << "Job " << job->getJobNumber() << " was made CO2 neutral with the support of \"" << job->getCompensationName() << "\"." << endl;
    }

    onStream << endl;
}

void System::divideJobs() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling divideJobs");
    for(auto job: _jobs){
        // choose device
        Device* appropiate_device = pick_device(this, job);

        appropiate_device->add_job(job);

        find_compensation(job);
    }
}

void System::tick() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling tick");
    for (auto device : _devices) {
        if(device->print(current_time)){
            if(!device->getCurrentJob()->getCompensated()){
                this->totalCO2emission += device->get_emissions();
            }
        }
    }

    current_time++;
}

void System::calculateStatistics() {

    int totalCosts = 0;
    for(auto device : _devices){
        totalCosts += device->get_total_pages() * device->getCosts();
    }
    totalOperatingCosts = totalCosts;




    Device* most_used_dev = nullptr;
    long long unsigned int queue_size = 0;
    for(auto device : _devices){
        if(device->get_queue().size() > queue_size){
            queue_size = device->get_queue().size();
            most_used_dev = device;
        }
    }
    mostUsedDevice = most_used_dev;




    double average = 0; // CO2 per page
    double counter = 0;
    for(auto device : _devices){
        average += device->get_emissions();
        counter ++;
    }

    average = average / counter;
    averageCO2perPage = average;



    Compensation* compensation = nullptr;
    counter = 0;
    for(auto comp : _compensations){
        if(counter < comp->getCounter()){
            counter = comp->getCounter();
            compensation = comp;
        }
    }
    mostUsedCompensation = compensation;
}

int System::getTotalEmissions() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling getTotalEmissions");
    ENSURE(totalCO2emission >= 0, "totalCO2emission value must be greater or equal than 0");
    return totalCO2emission;
}

int System::getTotalOperatingCosts() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling getTotalOperatingCosts");
    ENSURE(totalOperatingCosts >= 0, "totalOperatingCosts value must be greater or equal than 0");
    return totalOperatingCosts;
}

Device *System::getMostUsedDevice() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling getMostUsedDevice");

    return mostUsedDevice;
}

double System::getAverageCO2perPage() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling getAverageCO2perPage");
    ENSURE(averageCO2perPage >= 0, "Average CO2 per page must be greater or equal than 0");
    return averageCO2perPage;
}

Compensation *System::getMostUsedCompensation() {
    REQUIRE(properlyInitialized(), "System wasn't initialized when calling getMostUsedCompensation");
    return mostUsedCompensation;
}
