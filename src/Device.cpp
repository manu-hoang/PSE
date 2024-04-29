#include "Device.h"
#include "SystemExporter.h"
#include "iostream"
#include <queue>
#include "contracts/DesignByContract.h"

Device::Device(string name, int emissions, double speed, int cost): name(name), emissions(emissions), speed(speed), cost(cost) {
    REQUIRE(speed >= 0, "Speed value must be greater or equal than 0");
    REQUIRE(emissions >= 0, "Emissions value must be greater or equal than 0");
    REQUIRE(cost >= 0, "Cost value must be greater or equal than 0");

    _initCheck = this;

    busy = false;
    _queue = {};

    CO2_value = 0;

    ENSURE(busy == false, "Device must not be busy after being initialized");
    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
    ENSURE(_queue.empty(), "queue must be empty when initialized");
    ENSURE(CO2_value == 0, "CO2_value must be 0 when initialized");
}

bool Device::properlyInitialized() {
    return _initCheck == this;
}

void Device::add_job(Job *job) {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling add_job");
    REQUIRE(job != nullptr, "Cannot add nullptr as job to device");

    this->busy = true;

    job->setDeviceName(this->name);

    job->setQueuePosition(_queue.size());
    this->_queue.push(job);

    ENSURE(this->busy == true, "add_job post condition failure");
}

Job *Device::getCurrentJob() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getCurrentJob");
    if(_queue.empty()){return nullptr;}
    return _queue.front();
}

queue<Job *> Device::get_queue() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_queue");
    return this->_queue;
}

int Device::get_emissions() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_emissions");
    ENSURE(this->emissions >= 0, "this->emissions value must be greater or equal than 0");
    return this->emissions;
}

int Device::get_CO2() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_CO2");
    ENSURE(CO2_value >= 0, "CO2_value value must be greater or equal than 0");
    return CO2_value;
}

void Device::set_CO2(int value) {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling set_CO2");
    REQUIRE(value >= 0, "value must be non-negative");
    CO2_value = value;
}

string Device::getName() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getName");
    return name;
}

string Device::getEmissions() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getEmissions");
    return to_string(emissions);
}

string Device::getSpeed() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getSpeed");
    return to_string(speed);
}

string Device::getType() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getType");

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

string Device::getTypeJob() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getType");

    switch (this->get_type()) {
        case bw_device:
            return "black-and-white";

        case color_device:
            return "color";

        case scan_device:
            return "scanner";

        case invalid_device:
            return "unsupported device";
    }

    return "";
}

int Device::getCosts() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getCosts");
    ENSURE(cost >= 0, "cost value must be greater or equal than 0");
    return cost;
}

void Device::updatePositions(int totalRunTime) {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling popQueue");
    REQUIRE(totalRunTime >= 0, "totalRunTime value must be equal or higher then 0");
    ::queue<Job*> temp = {};

    for (long long unsigned int i = 0; i < _queue.size(); ++i) {
        _queue.front()->setQueuePosition(i);
        _queue.front()->setStartTime(totalRunTime);
        _queue.front()->set_busy(true);
        temp.push(_queue.front());
        _queue.pop();
    }

    _queue = temp;
}

bool Device::print(int totalRunTime) {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling print");
    REQUIRE(totalRunTime >= 0, "totalRunTime value must be equal or higher then 0");
    if(_queue.size() == 0){
        // no job to print
        this->busy = false;
        return false;
    }
    bool page_printed = false;

    this->getCurrentJob()->set_busy(true);

    double interval = this->getCurrentJob()->calculatePrintingTimePage(speed);

    if(totalRunTime >= interval){
        this->getCurrentJob()->printFullPage();
        page_printed = true;
    }

    if(this->getCurrentJob()->getFinished()){
        popQueue();
        updatePositions(totalRunTime);
    }
    ENSURE(busy == true, "Device must be busy after print is called");
    return page_printed;
}

void Device::popQueue() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling popQueue");
    this->_queue.pop();
}

bool Device::exceeds_CO2_limit(int value) {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling exceeds_CO2_limit");
    if(value > this->CO2_limit){return true;}
    return false;
}

void Device::set_limit(int limit) {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling set_limit");
    REQUIRE(limit >= 0, "value must be non-negative");
    this->CO2_limit = limit;
}

int Device::get_limit() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_limit");
    ENSURE(CO2_limit >= 0, "CO2_limit value must be greater or equal than 0");
    return CO2_limit;
}

int Device::get_total_pages() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_total_pages");
    if(this->_queue.size() == 0){return 0;}

    int total = 0;

    auto copy = this->get_queue();

    for (long long unsigned int i = 0; i < copy.size(); ++i) {
        total += copy.front()->getTotalPageCount();
        copy.pop();
    }
    ENSURE(total >= 0, "total value must be greater or equal than 0");
    return total;
}

int Device::get_speed() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_speed");
    ENSURE(this->speed >= 0, "this->emissions value must be greater or equal than 0");
    return this->speed;
}

BlackWhitePrinter::BlackWhitePrinter(string name, int emissions, double speed, int cost) : Device(name, emissions, speed, cost) {
    // CO2 limit
    REQUIRE(speed >= 0, "Speed value must be greater or equal than 0");
    REQUIRE(emissions >= 0, "Emissions value must be greater or equal than 0");
    REQUIRE(cost >= 0, "Cost value must be greater or equal than 0");
    this->set_limit(8);
    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
}

DeviceEnum BlackWhitePrinter::get_type() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_type");
    return bw_device;
}

ColorPrinter::ColorPrinter(string name, int emissions, double speed, int cost) : Device(name, emissions, speed, cost) {
    // CO2 limit
    REQUIRE(speed >= 0, "Speed value must be greater or equal than 0");
    REQUIRE(emissions >= 0, "Emissions value must be greater or equal than 0");
    REQUIRE(cost >= 0, "Cost value must be greater or equal than 0");
    this->set_limit(23);
    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
}

DeviceEnum ColorPrinter::get_type() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_type");
    return color_device;
}

Scanner::Scanner(string name, int emissions, double speed, int cost) : Device(name, emissions, speed, cost) {
    REQUIRE(speed >= 0, "Speed value must be greater or equal than 0");
    REQUIRE(emissions >= 0, "Emissions value must be greater or equal than 0");
    REQUIRE(cost >= 0, "Cost value must be greater or equal than 0");
    // CO2 limit
    this->set_limit(12);
    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
}

DeviceEnum Scanner::get_type() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_type");
    return scan_device;
}
