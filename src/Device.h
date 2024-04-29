#pragma once

#include <queue>
#include "string"
#include "Job.h"

using namespace std;

/*
    TOTAL EMISSIONS LIMITS:

    Device type                 CO2 limit
    Black-and-white printers    8g CO2 per page
    Color printers              23g CO2 per page
    Scanner                     12g CO2 per page
*/

enum DeviceEnum {bw_device, color_device, scan_device, invalid_device};

class Device {
public:

    /**
    \n REQUIRE(emissions >= 0, "Emissions must be non-negative");
    \n REQUIRE(speed >= 0, "Speed must be non-negative");
    \n REQUIRE(cost >= 0, "Cost must be non-negative");
    \n ENSURE(busy == false, "Device must not be busy after being initialized");
    \n ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
    \n ENSURE(_queue.empty(), "queue must be empty when initialized");
    \n ENSURE(CO2_value == 0, "CO2_value must be 0 when initialized");
    */
    Device(string name, int emissions, double speed, int cost);

    virtual DeviceEnum get_type() = 0;

    bool properlyInitialized();

    /**
    \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling print");
    \n REQUIRE(totalRunTime >= 0, "totalRunTime value must be equal or higher then 0");
    \n ENSURE(busy == true, "Device must be busy after print is called");
    */
    bool print(int totalRunTime); // print for 1 second

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling popQueue");
    */
    void popQueue();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling updatePositions");
     \n REQUIRE(totalRunTime >= 0, "totalRunTime value must be equal or higher then 0");
    */
    void updatePositions(int totalRunTime);

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getCurrentJob");
    */
    Job* getCurrentJob();

    /**
    \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling add_job");
    \n REQUIRE(job != nullptr, "Cannot add nullptr as job to device");
    \n ENSURE(this->busy == true, "add_job post condition failure");
    */
    void add_job(Job *job);

    /**
    \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_queue");
    */
    queue<Job*> get_queue();

    /**
    \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_CO2");
    \n ENSURE(CO2_value >= 0, "CO2_value value must be greater or equal than 0");
    */
    int get_CO2();

    /**
    \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling set_CO2");
    \n REQUIRE(value >= 0, "value must be non-negative");
    */
    void set_CO2(int value);

    /**
    \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling exceeds_CO2_limit");
    */
    bool exceeds_CO2_limit(int value);

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_emissions");
     \n ENSURE(this->emissions >= 0, "this->emissions value must be greater or equal than 0");
    */
    int get_emissions();

    /**
    \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_speed");
    \n ENSURE(this->speed >= 0, "this->speed value must be greater or equal than 0");
    */
    int get_speed();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_total_pages");
     \n ENSURE(total >= 0, "total value must be greater or equal than 0");
    */
    int get_total_pages();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_limit");
     \n ENSURE(CO2_limit >= 0, "CO2_limit value must be greater or equal than 0");
    */
    int get_limit();

    // Use Case 2.2, Simple Output

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getName");
    */
    string getName();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getEmissions");
    */
    string getEmissions();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getSpeed");
    */
    string getSpeed();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getType");
    */
    string getType();

    /**
    \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getType");
    */
    string getTypeJob();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getCosts");
     \n ENSURE(cost >= 0, "cost value must be greater or equal than 0");
    */
    int getCosts();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling set_limit");
     \n REQUIRE(limit >= 0, "value must be non-negative");
    */
    void set_limit(int limit);

private:
    Device* _initCheck; //!use pointer to myself to verify whether I am properly initialized

    string name;

    int CO2_value; // current device value
    int CO2_limit; // limit

    int emissions; // gram CO2 per page

    int speed; // pages per minute

    int cost; // cents per page

    bool busy;

    queue<Job*> _queue;
};

class BlackWhitePrinter : public Device {
public:
    BlackWhitePrinter(string name, int emissions, double speed, int cost);

    DeviceEnum get_type() override;
};

class ColorPrinter : public Device {
public:
    ColorPrinter(string name, int emissions, double speed, int cost);

    DeviceEnum get_type() override;
};

class Scanner : public Device {
public:
    Scanner(string name, int emissions, double speed, int cost);

    DeviceEnum get_type() override;
};
