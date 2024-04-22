#include "Device.h"
#include "SystemExporter.h"
#include "iostream"
#include "contracts/DesignByContract.h"

Device::Device(string name, int emissions, double speed, int cost): name(name), emissions(emissions), speed(speed), cost(cost) {
    REQUIRE(speed >= 0, "Constructor requires speed to be greater or equal than 0");
    REQUIRE(emissions >= 0, "Emissions value must be greater or equal than 0");

    _initCheck = this;

    busy = false;
    queue = {};

    ENSURE(busy == false, "Device must not be busy after being initialized");
    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
}

bool Device::properlyInitialized() {
    return _initCheck == this;
}

void Device::add_job(Job *job) {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling add_job");

    this->busy = true;

    this->queue.push(job);

    ENSURE(this->busy == true, "add_job post condition failure");
}

bool Device::getBusy() {
    REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getBusy");
    return busy;
}

Job *Device::getCurrentJob() {
    return queue.front();
}

// Auxiliary function for internal use only

string get_type(Job* job){
    string type;

    JobEnum type_enum = job->get_type();

    switch(type_enum){
        case bw_job:
            type = "black-and-white";
            break;

        case color_job:
            type = "color-printing";
            break;

        case scan_job:
            type = "scanning";
            break;

        case invalid_job: // should never be invalid
            type = "invalid";
            break;
    }

    return type;
}

void Device::writeOn(ostream &onStream) {

    Job* job = queue.front();

    string job_type = ::get_type(job);

    cout << "Printer \"" << this->name << "\" finished " << job_type << " job:" << endl;
    cout << "\tNumber " << job->getJobNumber() << endl;
    cout << "\tSubmitted by \"" << job->getUserName() << "\"" << endl;
    cout << "\t" << job->getTotalPageCount() << " pages" << endl << endl;
}

BlackWhitePrinter::BlackWhitePrinter(string &name, int emissions, double speed, int cost) : Device(name, emissions, speed, cost) {

}

DeviceEnum BlackWhitePrinter::get_type() {
    return bw_device;
}

ColorPrinter::ColorPrinter(string &name, int emissions, double speed, int cost) : Device(name, emissions, speed, cost) {

}

DeviceEnum ColorPrinter::get_type() {
    return color_device;
}

Scanner::Scanner(string &name, int emissions, double speed, int cost) : Device(name, emissions, speed, cost) {

}

DeviceEnum Scanner::get_type() {
    return scan_device;
}
