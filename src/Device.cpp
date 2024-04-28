#include "Device.h"
#include "SystemExporter.h"
#include "iostream"
#include <queue>
#include "contracts/DesignByContract.h"

Device::Device(string name, int emissions, double speed, int cost): name(name), emissions(emissions), speed(speed), cost(cost) {
    REQUIRE(speed >= 0, "Constructor requires speed to be greater or equal than 0");
    REQUIRE(emissions >= 0, "Emissions value must be greater or equal than 0");

    _initCheck = this;

    busy = false;
    queue = {};

    CO2_value = 0;

    ENSURE(busy == false, "Device must not be busy after being initialized");
    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
}

bool Device::properlyInitialized() {
    return _initCheck == this;
}

void Device::add_job(Job *job) {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling add_job");

    this->busy = true;

    job->setDeviceName(this->name);

    job->setQueuePosition(queue.size());
    this->queue.push(job);

    ENSURE(this->busy == true, "add_job post condition failure");
}

Job *Device::getCurrentJob() {
    return queue.front();
}

queue<Job *> Device::get_queue() {
    return this->queue;
}

void Device::set_limit(int limit) {
    this->CO2_limit = limit;
}

int Device::get_emissions() {
    return this->emissions;
}

int Device::get_CO2() {
    return CO2_value;
}

void Device::set_CO2(int value) {
    CO2_value = value;
}

int Device::get_limit() {
    return CO2_limit;
}

string Device::getName() {
    return name;
}

string Device::getEmissions() {
    return to_string(emissions);
}

string Device::getSpeed() {
    return to_string(speed);
}

string Device::getType() {

    switch (this->get_type()) {
        case bw_device:
            return "Black-and-white printer";

        case color_device:
            return "Color printer";

        case scan_device:
            return "Scanner";

        case invalid_device:
            return "Unsupported device";
    }

    return "";
}

string Device::getCosts() {
    return to_string(cost);
}

void Device::updatePositions(int totalRunTime) {

    ::queue<Job*> temp = {};

    for (long long unsigned int i = 0; i < queue.size(); ++i) {
        queue.front()->setQueuePosition(i);
        queue.front()->setStartTime(totalRunTime);
        queue.front()->set_busy(true);
        temp.push(queue.front());
        queue.pop();
    }

    queue = temp;
}

void Device::print(int totalRunTime) {
    if(queue.size() == 0){
        // no job to print
        this->busy = false;
        return;
    }

    this->getCurrentJob()->set_busy(true);

    double interval = this->getCurrentJob()->calculatePrintingTimePage(speed);

    if(totalRunTime >= interval){
        this->getCurrentJob()->printFullPage();
    }

    if(this->getCurrentJob()->getFinished()){
        popQueue();
        updatePositions(totalRunTime);
    }
}

void Device::popQueue() {
    this->queue.pop();
}

bool Device::exceeds_CO2_limit(int value) {
    if(value > this->CO2_limit){return true;}
    return false;
}

BlackWhitePrinter::BlackWhitePrinter(string &name, int emissions, double speed, int cost) : Device(name, emissions, speed, cost) {
    // CO2 limit
    this->set_limit(8);
}

DeviceEnum BlackWhitePrinter::get_type() {
    return bw_device;
}

ColorPrinter::ColorPrinter(string &name, int emissions, double speed, int cost) : Device(name, emissions, speed, cost) {
    // CO2 limit
    this->set_limit(23);
}

DeviceEnum ColorPrinter::get_type() {
    return color_device;
}

Scanner::Scanner(string &name, int emissions, double speed, int cost) : Device(name, emissions, speed, cost) {
    // CO2 limit
    this->set_limit(12);
}

DeviceEnum Scanner::get_type() {
    return scan_device;
}
