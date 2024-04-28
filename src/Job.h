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
    */
    Job(int jobNumber, double pageCount, string userName);

    virtual JobEnum get_type() = 0;

    bool properlyInitialized();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling print_page");
     \n ENSURE(_currentPageCount == old_page_count - 1, "Job did not print page correctly");

     \n if page count <= 0:
     \n     ENSURE(_finished, "Job must be in finished state if no pages are left");
    */
    void printFullPage();

    bool get_busy();
    void set_busy(bool busy);

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getFinished");
    */
    bool getFinished();

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getJobNumber");
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
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getUserName");
    */
    string &getUserName();

    // Use Case 2.2, Simple Output
    string getOwner();
    string getDevice();
    string getStatus();
    string getTotalPages();
    string getTotalCO2();
    string getTotalCost();
    string getType();

    void setDeviceName(string name);
    void setCompensationName(string name);
    void setQueuePosition(int position);

protected:
    string device_name;
    string compensation_name;

    int queue_position;

    int _totalPageCount;
    int _currentPageCount;

    bool busy;
    bool _finished;

private:
    Job* _initCheck; //!use pointer to myself to verify whether I am properly initialized

    int _jobNumber;
    string _userName;
};

class BlackWhiteJob : public Job {
public:
    BlackWhiteJob(int jobNumber, double pageCount, string userName);

    JobEnum get_type() override;
};

class ColorJob : public Job {
public:
    ColorJob(int jobNumber, double pageCount, string userName);

    JobEnum get_type() override;
};


class ScanJob : public Job {
public:
    ScanJob(int jobNumber, double pageCount, string userName);

    JobEnum get_type() override;
};



