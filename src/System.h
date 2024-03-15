#pragma once

#include "vector"

#include "Device.h"
#include "Job.h"

class System {
public:
    /**
     \n System initializer, contains a vector for all jobs and all devices

     \n ENSURE(properlyInitialized(), "Constructor must end in properlyInitialized state");
     \n ENSURE(_devices.empty(), "Devices vector must be empty after initialization");
     \n ENSURE(_jobs.empty(), "Jobs vector must be empty after initialization");
     \n ENSURE(current_time == 0, "time must start at 0 after initialization");
    */
    System();

    bool properlyInitialized();

    /**
     \n Main program while loop
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling automatic_run");
     \n REQUIRE(seconds >= 0, "Automatic run time must be a positive integer");
    */
    void automatic_run(int seconds);

    /**
     \n Divides jobs to their respective printers, currently just first printer in the system
     \n TODO: change this function to support multiple devices (system 2.0)

     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling link_jobs");
     \n REQUIRE(!_devices.empty(), "No device available to give jobs to");
     \n REQUIRE(current_time >= 0, "Current time must be a positive integer");
    */
    void link_jobs();

    /**
     \n Calls update function on all devices (see Device::update_current_job(int time) for more information)
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling update_all_devices");
    */
    void update_all_devices();

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling process_all_jobs");

     \n if device has a current job (is busy):
     \n     ENSURE(!device->getBusy(), "Device must have a current job to process");
     \n     REQUIRE(current_job != nullptr, "Printing finish time must be greater than 0");
     \n     REQUIRE(finish_time >= 0, "Printing finish time must be greater than 0");

     \n     if job is finished:
     \n         ENSURE(current_job->getFinished(), "current job must be finished after printing all pages");
    */
    void process_all_jobs();

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling addDevice");
     \n REQUIRE(device != nullptr, "Cannot add nullptr as device to system");
    */
    void addDevice(Device* &device);

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling addJob");
     \n REQUIRE(job != nullptr, "Cannot add nullptr as device to system");
    */
    void addJob(Job* &job);

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getDevices");
    */
    std::vector<Device*>& getDevices();

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getJobs");
    */
    vector<Job *> &getJobs();

private:
    System* _initCheck; //!use pointer to myself to verify whether I am properly initialized

    vector<Device*> _devices;
    vector<Job*> _jobs;

    int current_time;
};