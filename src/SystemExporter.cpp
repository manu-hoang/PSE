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
    return _documentStarted;
}


void SystemExporter::simple_output (std::ostream& onStream, System &system) {
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

        whitespace(onStream);
    }

    compensationStart(onStream);
    whitespace(onStream);

    systemEnd(onStream);

    documentEnd(onStream);
}

void SystemExporter::documentStart (std::ostream& onStream) {_documentStarted = true;}
void SystemExporter::documentEnd (std::ostream& onStream) {_documentStarted = false;}

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
    onStream << "[Job #" << job->getOwner() << "]" << std::endl;
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
    onStream << "* Total pages: " << job->getTotalPages() << std::endl;
}

void SystemExporter::jobTotalCO2(ostream &onStream, Job *job) {
    onStream << "* Total CO2: " << job->getTotalCO2() << std::endl;
}

void SystemExporter::jobTotalCost(ostream &onStream, Job *job) {
    onStream << "*  Total cost: " << job->getTotalCost()<< std::endl;
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