#pragma once

#include <queue>
#include "string"
#include "Job.h"

using namespace std;

/*
    Device type                 CO2 limit
    Black-and-white printers    8g CO2 per page
    Color printers              23g CO2 per page
    Scanner                     12g CO2 per page
*/

enum DeviceEnum {bw_device, color_device, scan_device, invalid_device};

class Device {
public:

    /**
     \n Device initializer

     \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     \n REQUIRE(speed > 0, "Constructor requires speed to be greater than 0");
     \n REQUIRE(emissions > 0, "Constructor requires emissions to be greater than 0");

     \n ENSURE(busy = false, "Device must not be busy after being initialized");
     \n ENSURE(current_job = nullptr, "Device must have no current job after being initialized");
    */
    Device(string name, int emissions, double speed, int cost);

    virtual DeviceEnum get_type() = 0;

    bool properlyInitialized();

    Job* getCurrentJob();

    void writeOn(std::ostream& onStream);

    /**
    \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling add_job");
    \n ENSURE(this->busy == true, "add_job post condition failure");
    \n ENSURE(queue.size() == copy.size() + 1, "add_job post condition failure");
    */
    void add_job(Job *job);

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getBusy");
    */
    bool getBusy();

private:
    Device* _initCheck; //!use pointer to myself to verify whether I am properly initialized

    string name;
    int emissions; // gram CO2 per page
    double speed; // pages per minute
    double cost;

    bool busy;

    queue<Job*> queue;

    double printing_time; // time to complete current job (seconds)
};

class BlackWhitePrinter : public Device {
public:
    BlackWhitePrinter(string &name, int emissions, double speed, int cost);

    DeviceEnum get_type() override;
};

class ColorPrinter : public Device {
public:
    ColorPrinter(string &name, int emissions, double speed, int cost);

    DeviceEnum get_type() override;
};

class Scanner : public Device {
public:
    Scanner(string &name, int emissions, double speed, int cost);

    DeviceEnum get_type() override;
};
