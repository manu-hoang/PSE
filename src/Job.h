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
    virtual void print_page() = 0;

    bool get_busy();
    void set_busy(bool busy);

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setStartTime");
     \n REQUIRE(time >= 0, "Job starting time must be a positive integer");
     \n ENSURE(_start_time == time, "setStartTime post condition failure");
    */
    void setStartTime(int time);

    /**
     \n REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getStartTime");
     \n ENSURE(_start_time >= 0, "Starting time must be a positive integer");
    */
    int getStartTime();

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

protected:
    Job* _initCheck; //!use pointer to myself to verify whether I am properly initialized

    int _jobNumber;

    double _totalPageCount;
    double _currentPageCount;

    string _userName;

    bool busy;
    double _start_time;
    bool _finished;
};

class BlackWhiteJob : public Job {
public:
    BlackWhiteJob(int jobNumber, double pageCount, string userName);

    JobEnum get_type() override;

    void print_page() override;
};

class ColorJob : public Job {
public:
    ColorJob(int jobNumber, double pageCount, string userName);

    JobEnum get_type() override;

    void print_page() override;
};


class ScanJob : public Job {
public:
    ScanJob(int jobNumber, double pageCount, string userName);

    JobEnum get_type() override;

    void print_page() override;
};



