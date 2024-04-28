//============================================================================
// Name        : TicTacToeExporter.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include "contracts/DesignByContract.h"
#include "SystemExporter.h"

using namespace std;


SystemExporter::SystemExporter() {
    _initCheck = this;
    _documentStarted = false;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}


bool SystemExporter::properlyInitialized() {
    return _initCheck == this;
}

bool SystemExporter::documentStarted() {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling documentStarted");
    return _documentStarted;
}


void SystemExporter::simple_output (std::ostream& onStream, System &system) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling simple_output");
    REQUIRE(documentStarted(), "Document was not started when calling simple_output");

    documentStart(onStream);

    systemStart(onStream, "System Status");
    whitespace(onStream);

    devicesStart(onStream);
    whitespace(onStream);

    for(auto device : system.getDevices()){
        deviceName(onStream, device);
        deviceEmissions(onStream, device);
        deviceSpeed(onStream, device);
        deviceType(onStream, device);
        deviceCosts(onStream, device);

        whitespace(onStream);
    }

    jobsStart(onStream);
    whitespace(onStream);

    for(auto job : system.getJobs()){
        jobNumber(onStream, job);
        jobOwner(onStream, job);
        jobDevice(onStream, job);
        jobStatus(onStream, job);
        jobTotalPages(onStream, job);
        jobTotalCO2(onStream, job);
        jobTotalCost(onStream, job);

        if(job->getCompensated()){
            onStream << "* Compensation: " << job->getCompensationName() << std::endl;
        }

        whitespace(onStream);
    }

    compensationStart(onStream);
    for(auto compensation : system.getCompensations()){
        onStream << compensation->getName() << " [#" << compensation->getCompNumber() << "]" << endl;
    }
    whitespace(onStream);

    systemEnd(onStream);

    documentEnd(onStream);
}

string display(Job* job){
    return "[" + to_string(job->getCurrentPageCount()) + "/" + to_string(job->getTotalPageCount()) + "]";
}

void SystemExporter::advanced_textual_output(ostream &onStream, System &system) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling advanced_textual_output");
    REQUIRE(documentStarted(), "Document was not started when calling simple_output");

    for(auto device : system.getDevices()){
        onStream << device->getName() << endl;
        auto queue = device->get_queue();

        int counter = 0;

        onStream << "   ";

        while(!queue.empty()){
            onStream << display(queue.front()) << " ";
            queue.pop();
            counter++;

            if(counter == 1){
                onStream << " | ";
                counter++;
            }
        }

        onStream << endl;
    }
    onStream << endl;
}

void SystemExporter::documentStart (std::ostream& onStream) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling documentStart");
    _documentStarted = true;
    ENSURE(documentStarted(), "Failed post condition documentStart");
}

void SystemExporter::documentEnd (std::ostream& onStream) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling documentEnd");
    _documentStarted = false;
    ENSURE(!documentStarted(), "Failed post condition documentEnd");
}

void SystemExporter::systemStart (std::ostream& onStream, const string title) {
    onStream << "# === [" << title << "] === #" << std::endl;
}

void SystemExporter::devicesStart (std::ostream& onStream) {
    onStream << "--== Devices ==--" << std::endl;
}

void SystemExporter::deviceName(ostream &onStream, Device *device) {
    onStream << device->getName() << ":" << std::endl;
}

void SystemExporter::deviceEmissions(ostream &onStream, Device *device) {
    onStream << "* " << device->getEmissions() << "g/page" << std::endl;
}

void SystemExporter::deviceSpeed(ostream &onStream, Device *device) {
    onStream << "* " << device->getSpeed() << " pages / minute" << std::endl;
}

void SystemExporter::deviceType(ostream &onStream, Device *device) {
    onStream << "* " << device->getType() << std::endl;
}

void SystemExporter::deviceCosts(ostream &onStream, Device *device) {
    onStream << "* " << device->getCosts() << " cents / page"<< std::endl;
}

void SystemExporter::jobsStart (std::ostream& onStream) {
    onStream << "--== Jobs ==--" << std::endl;
}

void SystemExporter::jobNumber(ostream &onStream, Job *job) {
    onStream << "[Job #" << job->getJobNumber() << "]" << std::endl;
}

void SystemExporter::jobOwner(ostream &onStream, Job *job) {
    onStream << "* Owner: " << job->getOwner() << std::endl;
}

void SystemExporter::jobDevice(ostream &onStream, Job *job) {
    onStream << "* Device: " << job->getDevice() << std::endl;
}

void SystemExporter::jobStatus(ostream &onStream, Job *job) {
    onStream << "* Status: " << job->getStatus() << std::endl;
}

void SystemExporter::jobTotalPages(ostream &onStream, Job *job) {
    onStream << "* Total pages: " << job->getTotalPages() << " pages" << std::endl;
}

void SystemExporter::jobTotalCO2(ostream &onStream, Job *job) {
    onStream << "* Total CO2: " << job->getTotalCO2() << "g CO2"<< std::endl;
}

void SystemExporter::jobTotalCost(ostream &onStream, Job *job) {
    onStream << "* Total cost: " << job->getTotalCost() << " cents" << std::endl;
}

void SystemExporter::compensationStart (std::ostream& onStream) {
    onStream << "--== Co2 Compensation initiatives ==--" << std::endl;
}

void SystemExporter::whitespace(ostream &onStream) {
    onStream << endl;
}

void SystemExporter::systemEnd (std::ostream& onStream) {
    onStream << "# ======================= #" << std::endl;
}

void SystemExporter::statistics_output(ostream &onStream, System &system) {
    system.calculateStatistics();

    onStream << "Interesting Statistics: " << endl << endl;

    onStream << "Total operating costs: " << system.getTotalOperatingCosts() << endl;
    onStream << "Total CO2 emission: " << system.getTotalEmissions() << endl;
    onStream << "Average CO2 per page: " << system.getTotalOperatingCosts() << endl;
    if(system.getMostUsedDevice() != nullptr){
        onStream << "Most used device currently: " << system.getMostUsedDevice()->getName() << endl;
    } else{ onStream << "Most used device currently: No active devices" << endl;}

    if(system.getMostUsedCompensation() != nullptr) {
        onStream << "Most used compensation: " << system.getMostUsedCompensation()->getName() << endl;
    } else{ onStream << "Most used compensation: No compensations" << endl;}
}
