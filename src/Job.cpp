#include "Job.h"
#include "contracts/DesignByContract.h"
#include "iostream"

Job::Job(int jobNumber, double totalPageCount, string userName) : _totalPageCount(totalPageCount), _jobNumber(jobNumber), _userName(userName){
    REQUIRE(totalPageCount >= 0, "Job page count must be a positive integer");
    REQUIRE(jobNumber >= 0, "Job id number must be a positive integer");
    _initCheck = this;

    busy = false;
    _finished = false;
    _currentPageCount = totalPageCount;

    ENSURE(properlyInitialized(),"Constructor must end in properlyInitialized state");
    ENSURE(!_finished,"Job cannot be in a finished state after initialization");
    ENSURE(_currentPageCount == totalPageCount, "current page count must be equal to total page count after initialization");
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
    this->busy = input;
}

bool Job::get_busy() {
    return busy;
}

string Job::getOwner() {
    return _userName;
}

string Job::getDevice() {
    return _userName;
}

string Job::getStatus() {
    return _userName;
}

string Job::getTotalPages() {
    return _userName;
}

string Job::getTotalCO2() {
    return _userName;
}

string Job::getTotalCost() {
    return _userName;
}

BlackWhiteJob::BlackWhiteJob(int jobNumber, double pageCount, string userName) : Job(jobNumber, pageCount, userName) {

}

JobEnum BlackWhiteJob::get_type() {
    return bw_job;
}

ColorJob::ColorJob(int jobNumber, double pageCount, string userName) : Job(jobNumber, pageCount, userName) {

}

JobEnum ColorJob::get_type() {
    return color_job;
}

ScanJob::ScanJob(int jobNumber, double pageCount, string userName) : Job(jobNumber, pageCount, userName) {

}

JobEnum ScanJob::get_type() {
    return scan_job;
}

void Job::printFullPage() {
    REQUIRE(properlyInitialized(), "Job wasn't initialized when calling print_page");

    _currentPageCount--;

    if(_currentPageCount <= 0){
        _finished = true;
        busy = false;
    }
}

void Job::setDeviceName(string name) {
    this->device_name = name;
}

void Job::setCompensationName(string name) {
    this->compensation_name = name;
}

void Job::setQueuePosition(int position) {
    this->queue_position = position;
}
