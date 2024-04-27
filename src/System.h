#pragma once

#include "vector"

#include "Device.h"
#include "Job.h"
#include "Compensation.h"

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

    void divideJobs();

    void tick();

    void writeOn(ostream &onStream);

    void automated_processing();

    void manual_processing(Device* device);

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling addDevice");
     \n REQUIRE(device != nullptr, "Cannot add nullptr as device to system");
    */
    void addDevice(Device* &device);

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getDevices");
    */
    std::vector<Device*>& getDevices();

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling addJob");
     \n REQUIRE(job != nullptr, "Cannot add nullptr as job to system");
    */
    void addJob(Job* &job);

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getJobs");
    */
    vector<Job *> &getJobs();

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling addJob");
     \n REQUIRE(job != nullptr, "Cannot add nullptr as device to system");
    */
    void addCompensation(Compensation* compensation);

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getCompensations");
    */
    vector<Compensation*> getCompensations();

private:
    System* _initCheck; //!use pointer to myself to verify whether I am properly initialized

    vector<Device*> _devices;
    vector<Job*> _jobs;
    vector<Compensation*> _compensations;

    int current_time;
};