#pragma once

#include "string"

using namespace std;

enum JobEnum {bw_job, color_job, scan_job, invalid_job};

class Job {
public:
    /**
     \n Job initializer
     \n REQUIRE(pageCount >= 0, "Job page count must be a positive integer");
     \n REQUIRE(jobNumber >= 0, "Job id number must be a positive integer");
     \n ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
     \n ENSURE(!finished,"Job cannot be in a finished state after initialization");
     \n ENSURE(currentPageCount == totalPageCount, "current page count must be equal to total page count after initialization");
     \n ENSURE(!busy, "job must not be busy when initialized");
     \n ENSURE(!compensated, "job must not be compensated when initialized");
     \n ENSURE(start_time == 0, "start_time value must be 0 when initialized");
     \n ENSURE(totalCO2 == 0, "totalCO2 value must be 0 when initialized");
     \n ENSURE(totalCost == 0, "totalCO2 value must be 0 when initialized");
    */
    Job(int jobNumber, double pageCount, string userName, int compNumber);

    virtual JobEnum get_type() = 0;

    bool properlyInitialized();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling printFullPage");
    */
    void printFullPage();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling get_busy");
    */
    bool get_busy();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling set_busy");
    */
    void set_busy(bool busy);

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getFinished");
    */
    bool getFinished();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getJobNumber");
     \n ENSURE(_jobNumber >= 0, "_jobNumber must be a positive integer");
    */
    int getJobNumber();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getTotalPageCount");
     \n ENSURE(_totalPageCount >= 0, "Total page count must be a positive integer");
    */
    int getTotalPageCount();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getCurrentPageCount");
     \n ENSURE(_currentPageCount >= 0, "Current page count must be a positive integer");
    */
    int getCurrentPageCount();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setCurrentPageCount");
     \n REQUIRE(count >= 0, "count value must be equal or greater then 0");
    */
    void setCurrentPageCount(int count);

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling calculatePrintingTimePage");
     \n REQUIRE(speed >= 0, "speed value must be equal or greater then 0");
     \n ENSURE(start_time + (pagesPrinted + 1) * pagesPerSecond >= 0, "Printingtimepage must be equal or greater then 0");
    */
    double calculatePrintingTimePage(int speed); // input in pages per minute

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setStartTime");
     \n REQUIRE(time >= 0, "time value should be equal to or greater then 0");
    */
    void setStartTime(int time);

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setCompNumber");
     \n REQUIRE(value >= 0, "value should be greather then or equal to 0");
    */
    void setCompNumber(int compNumber);

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getCompNumber");
     \n ENSURE(compNumber >= 0, "compNumber value should be greater then or equal to 0");
    */
    int getCompNumber();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setCompensated");
    */
    void setCompensated(bool compensated);

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getCompensated");
    */
    bool getCompensated();

    // Use Case 2.2, Simple Output

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getType");
    */
    string getType();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getOwner");
    */
    string getOwner();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getDevice");
    */
    string getDevice();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getStatus");
    */
    string getStatus();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getTotalPages");
    */
    string getTotalPages();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getTotalCO2");
    */
    string getTotalCO2();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getTotalCost");
    */
    string getTotalCost();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getUseName");
    */
    string &getUserName();

    /**
    \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setDeviceName");
    */
    void setDeviceName(string name);

    /**
    \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setQueuePosition");
    \n REQUIRE(position >= 0, "position value should be greather then or equal to 0");
    */
    void setQueuePosition(int position);

    /**
    \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setCompensationName");
    */
    void setCompensationName(string name);
    /**
    \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getCompensationName");
    */
    string getCompensationName();

    /**
    \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setTotalCO2");
    \n REQUIRE(value >= 0, "value should be greater then or equal to 0");
    */
    void setTotalCO2(int value);

    /**
    \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setTotalCost");
    \n REQUIRE(value >= 0, "value should be greater then or equal to 0");
    */
    void setTotalCost(int value);

private:
    Job* _initCheck; //!use pointer to myself to verify whether I am properly initialized

    int _jobNumber;
    string _userName;

    int compNumber;
    bool compensated;

    string device_name;
    string compensation_name;

    int queue_position;

    int _totalPageCount;
    int _currentPageCount;

    int start_time;
    bool busy;
    bool _finished;

    int totalCO2;
    int totalCost;
};

class BlackWhiteJob : public Job {
public:
    BlackWhiteJob(int jobNumber, double pageCount, string userName, int compNumber);

    JobEnum get_type() override;
};

class ColorJob : public Job {
public:
    ColorJob(int jobNumber, double pageCount, string userName, int compNumber);

    JobEnum get_type() override;
};


class ScanJob : public Job {
public:
    ScanJob(int jobNumber, double pageCount, string userName, int compNumber);

    JobEnum get_type() override;
};



