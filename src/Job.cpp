#include "Job.h"
#include "contracts/DesignByContract.h"
#include "iostream"

Job::Job(int jobNumber, double totalPageCount, string userName, int compNumber) : _jobNumber(jobNumber), _userName(userName), compNumber(compNumber), _totalPageCount(totalPageCount){
    REQUIRE(totalPageCount >= 0, "Page count must be a positive integer");
    REQUIRE(jobNumber >= 0, "Job id number must be a positive integer");
    REQUIRE(compNumber >= 0, "Compensation number must be a positive integer");
    _initCheck = this;

    busy = false;
    _finished = false;

    compensated = false;

    start_time = 0;
    _currentPageCount = totalPageCount;

    totalCO2 = 0;
    totalCost = 0;

    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
    ENSURE(!_finished,"Job cannot be in a finished state after initialization");
    ENSURE(_currentPageCount == totalPageCount, "current page count must be equal to total page count after initialization");
    ENSURE(!busy, "job must not be busy when initialized");
    ENSURE(!compensated, "job must not be compensated when initialized");
    ENSURE(start_time == 0, "start_time value must be 0 when initialized");
    ENSURE(totalCO2 == 0, "totalCO2 value must be 0 when initialized");
    ENSURE(totalCost == 0, "totalCO2 value must be 0 when initialized");

}

bool Job::properlyInitialized() {
    return _initCheck == this;
}

bool Job::getFinished() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getFinished");
    return _finished;
}

int Job::getJobNumber() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getJobNumber");
    ENSURE(_jobNumber >= 0, "_jobNumber must be a positive integer");
    return _jobNumber;
}

int Job::getTotalPageCount() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getTotalPageCount");
    ENSURE(_totalPageCount >= 0, "Total page count must be a positive integer");
    return _totalPageCount;
}

int Job::getCurrentPageCount() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getCurrentPageCount");
    ENSURE(_currentPageCount >= 0, "Current page count must be a positive integer");
    return _currentPageCount;
}

string &Job::getUserName() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getUserName");
    return _userName;
}

void Job::set_busy(bool input) {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling set_busy");
    this->busy = input;
}

bool Job::get_busy() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling get_busy");
    return busy;
}

string Job::getOwner() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getOwner");
    return _userName;
}

string Job::getDevice() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getDevice");
    return this->device_name;
}

string Job::getStatus() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getStatus");

    if(this->busy){
        int pages_printed = this->getTotalPageCount() - this->getCurrentPageCount();

        return to_string(pages_printed) + " pages done";
    }

    else{
        return "WAITING #" + to_string(this->queue_position);
    }

    return _userName;
}

string Job::getTotalPages() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getTotalPages");
    return to_string(this->_totalPageCount);
}

string Job::getTotalCO2() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getTotalCO2");
    return to_string(this->totalCO2);
}

string Job::getTotalCost() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getTotalcost");
    return  to_string(this->totalCost);
}

BlackWhiteJob::BlackWhiteJob(int jobNumber, double pageCount, string userName, int compNumber) : Job(jobNumber, pageCount, userName, compNumber) {

}

JobEnum BlackWhiteJob::get_type() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getType");
    return bw_job;
}

ColorJob::ColorJob(int jobNumber, double pageCount, string userName, int compNumber) : Job(jobNumber, pageCount, userName, compNumber) {

}

JobEnum ColorJob::get_type() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getType");
    return color_job;
}

ScanJob::ScanJob(int jobNumber, double pageCount, string userName, int compNumber) : Job(jobNumber, pageCount, userName, compNumber) {

}

JobEnum ScanJob::get_type() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getType");
    return scan_job;
}

void Job::printFullPage() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling print_page");

    int initialPageCount = _currentPageCount;

    _currentPageCount--;

    if(_currentPageCount <= 0){
        _finished = true;
        busy = false;
    }
    ENSURE(_currentPageCount == initialPageCount - 1, "The _currentPageCount should have decreased by 1");
}

void Job::setDeviceName(string name) {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setDeviceName");

    this->device_name = name;
}

void Job::setCompensationName(string name) {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setCompensationName");
    this->compensation_name = name;
}

void Job::setQueuePosition(int position) {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setQueuePosition");
    REQUIRE(position >= 0, "position value should be greather then or equal to 0");
    this->queue_position = position;
}

void Job::setCurrentPageCount(int count) {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setCurrentPageCount");
    REQUIRE(count >= 0, "count value must be equal or greater then 0");
    this->_currentPageCount = count;
}

double Job::calculatePrintingTimePage(int speed) {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling calculatePrintingTimePage");
    REQUIRE(speed >= 0, "speed value must be equal or greater then 0");
    double pagesPerMinute = speed * 1.0;
    double pagesPerSecond = pagesPerMinute/60;

    int pagesPrinted = _totalPageCount - _currentPageCount;
    ENSURE(start_time + (pagesPrinted + 1) * pagesPerSecond >= 0, "PrintingTimePage must be equal or greater then 0");
    return start_time + (pagesPrinted + 1) * pagesPerSecond;
}

void Job::setStartTime(int time) {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setStartTime");
    REQUIRE(time >= 0, "time value should be equal to or greater then 0");
    this->start_time = time;
}

string Job::getType() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getType");

    switch (this->get_type()) {
        case bw_job:
            return "black-and-white";

        case color_job:
            return "color";

        case scan_job:
            return "scanning";

        case invalid_job:
            return "invalid";
    }
    return "";
}

bool Job::getCompensated() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getCompensated");

    return this->compensated;
}

void Job::setCompNumber(int value) {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setCompNumber");
    REQUIRE(value >= 0, "value should be greather then or equal to 0");
    this->compNumber = value;
}

int Job::getCompNumber() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getCompNumber");
    ENSURE(compNumber >= 0, "compNumber value should be greater then or equal to 0");
    return compNumber;
}

void Job::setCompensated(bool value) {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setCompensated");

    compensated = value;
}

string Job::getCompensationName() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling getCompensationName");

    return this->compensation_name;
}

void Job::setTotalCO2(int value) {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setTotalCO2");
    REQUIRE(value >= 0, "value should be greater then or equal to 0");
    totalCO2 = value;
}

void Job::setTotalCost(int value) {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling setTotalCost");
    REQUIRE(value >= 0, "value should be equal to or greater then 0");
    totalCost = value;
}
