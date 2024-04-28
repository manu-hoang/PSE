#pragma once

#include "vector"

#include "Device.h"
#include "Job.h"
#include "Compensation.h"

class System {
public:
    /**
     \n System initializer, contains a vector for all jobs and all devices

    */
    System();

    bool properlyInitialized();

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling divideJobs");
    */
    void divideJobs();

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling tick");
    */
    void tick();

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling automated_processing");
    */
    void automated_processing(std::ostream& onStream);

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling manual_processing");
    */
    void manual_processing(std::ostream& onStream, Device* device);

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling addDevice");
     \n REQUIRE(device != nullptr, "Cannot add nullptr as device to system");
    */
    void addDevice(Device* device);

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getDevices");
    */
    std::vector<Device*>& getDevices();

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling addJob");
     \n REQUIRE(job != nullptr, "Cannot add nullptr as job to system");
    */
    void addJob(Job* job);

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getJobs");
    */
    vector<Job *> getJobs();

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling addCompensation");
     \n REQUIRE(job != nullptr, "Cannot add nullptr as device to system");
    */
    void addCompensation(Compensation* compensation);

    /**
     \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getCompensations");
    */
    vector<Compensation*> getCompensations();

    /**
    \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getCompensations");
   */
    bool find_compensation(Job* job);

    /**
    \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getTotalEmissions");
    \n ENSURE(totalCO2emission >= 0, "totalCO2emission value must be greater or equal than 0");
    */
    int getTotalEmissions();

    // Statistics

    /**
    \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getCompensations");
   */
    void calculateStatistics();

    /**
    \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getTotalOperatingCosts");
    \n ENSURE(totalOperatingCosts >= 0, "totalOperatingCosts value must be greater or equal than 0");
    */
    int getTotalOperatingCosts();

    /**
    \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getMostUsedDevice");
   */
    Device* getMostUsedDevice();

    /**
    \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getAverageCO2perPage");
    \n ENSURE(averageCO2perPage >= 0, "Average CO2 per page must be greater or equal than 0");
    */
    double getAverageCO2perPage();

    /**
    \n REQUIRE(properlyInitialized(), "System wasn't initialized when calling getMostUsedCompensation");
   */
    Compensation* getMostUsedCompensation();


private:
    System* _initCheck; //!use pointer to myself to verify whether I am properly initialized

    vector<Device*> _devices;
    vector<Job*> _jobs;
    vector<Compensation*> _compensations;

    int current_time;

    // Statistics
    int totalOperatingCosts;
    Device* mostUsedDevice;
    int totalCO2emission;
    double averageCO2perPage;
    Compensation* mostUsedCompensation;
};