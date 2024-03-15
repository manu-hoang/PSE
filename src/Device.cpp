#include "Device.h"
#include "PrinterOutput.h"
#include "iostream"
#include "contracts/DesignByContract.h"

Device::Device(string name, int emissions, double speed): name(name), emissions(emissions), speed(speed) {
    REQUIRE(speed > 0, "Constructor requires speed to be greater than 0");
    REQUIRE(emissions > 0, "Emissions value must be greater than 0");

    _initCheck = this;

    busy = false;
    current_job = nullptr;

    ENSURE(busy == false, "Device must not be busy after being initialized");
    ENSURE(current_job == nullptr, "Device must have no current job after being initialized");
    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
}

bool Device::properlyInitialized() {
    return _initCheck == this;
}

void Device::print_page() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling print_page");
    REQUIRE(current_job != nullptr, "Unable to print page of nullptr");
    Job prev_copy = *current_job;

    // Use Case 3.1: Manual processing
    current_job->print_page();

    if(current_job->getFinished()){
        device_print_message(*this, current_job);
    }
}

void Device::update_current_job(int time){
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling update_current_job");

    if(current_job == nullptr){

        if(queue.empty()) {
            return; // nothing to update
        }
        else {
            current_job = queue[0];
            queue.erase(queue.begin());

            current_job->setStartTime(time);

            //amount of pages     // pages per second
            this->printing_time = current_job->getTotalPageCount() / (this->speed/60);

            busy = true;
            return;
        }
    }

    if(current_job->getFinished()){
        current_job = nullptr;
        busy = false;
        update_current_job(time);
    }
}

void Device::add_job(Job *&job) {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling add_job");

    this->busy = true;

    auto copy = queue;
    this->queue.push_back(job);

    ENSURE(this->busy == true, "add_job post condition failure");
    ENSURE(queue.size() == copy.size() + 1, "add_job post condition failure");
}

Job *Device::getCurrentJob() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getCurrentJob");
    return current_job;
}

vector<Job *> Device::getJobs() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getJobs");
    return queue;
}

double Device::get_printing_time() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_printing_time");
    REQUIRE(printing_time >= 0, "Printing time needs to be a positive integer");

    return printing_time;
}

string &Device::getName() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getName");
    return name;
}

int Device::getEmissions() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getEmissions");
    ENSURE(emissions > 0, "Emissions value must be greater than 0");
    return emissions;
}

bool Device::getBusy() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getBusy");
    return busy;
}