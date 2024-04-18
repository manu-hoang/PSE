#pragma once

#include <vector>
#include "string"
#include "Job.h"

using namespace std;

/*
    Device type                 CO2 limit
    Black-and-white printers    8g CO2 per page
    Color printers              23g CO2 per page
    Scanner                     12g CO2 per page
*/

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
    Device(string name, int emissions, double speed);

    bool properlyInitialized();

    /**
     \n Use Case 3.1: Manual processing
     \n Prints exactly one page from current job

     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling print_page");
     \n REQUIRE(current_job != nullptr, "unable to print page of nullptr");
    */
    void print_page();

    /**
     Note: Also calculates total printing time for current job (if updated)

     \n Updates the current job pointer to next in queue if finished.
     \n Simply returns if current job is finished and there are no jobs in the queue

     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling update_current_job");
    */
    void update_current_job(int current_time);

    /**
    \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling add_job");
    \n ENSURE(this->busy == true, "add_job post condition failure");
    \n ENSURE(queue.size() == copy.size() + 1, "add_job post condition failure");
    */
    void add_job(Job *&job);

    /**
    \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getCurrentJob");
    */
    Job* getCurrentJob();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getJobs");
    */
    vector<Job*> getJobs();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling get_printing_time");
    */
    double get_printing_time();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getName");
    */
    string &getName();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getEmissions");
     \n ENSURE(emissions > 0, "Emissions value must be greater than 0");
    */
    int getEmissions();

    /**
     \n REQUIRE(properlyInitialized(), "Device wasn't initialized when calling getBusy");
    */
    bool getBusy();

private:
    Device* _initCheck; //!use pointer to myself to verify whether I am properly initialized

    string name;
    // type? / subclass
    int emissions; // gram CO2 per page
    double speed; // pages per minute
    double cost;

    bool busy;

    Job* current_job;
    vector<Job*> queue; // excluding current job

    double printing_time; // time to complete current job (seconds)
};

class BlackWhitePrinter : public Device {
public:
    BlackWhitePrinter(string &name, int emissions, double speed);
};

class ColorPrinter : public Device {
public:
    ColorPrinter(string &name, int emissions, double speed);
};

class Scanner : public Device {
public:
    Scanner(string &name, int emissions, double speed);
};
