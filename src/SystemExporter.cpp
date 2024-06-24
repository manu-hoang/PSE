//============================================================================
// Name        : TicTacToeExporter.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include "contracts/DesignByContract.h"
#include "SystemExporter.h"
#include "../graphics_engine/engine.h"

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

string display(Job* job){
    return "[" + to_string(job->getCurrentPageCount()) + "/" + to_string(job->getTotalPageCount()) + "]";
}

string SystemExporter::advanced_textual_output_string(System &system) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling advanced_textual_output");

    string toPrint;

    for(auto device : system.getDevices()){
        toPrint += device->getName() + '\n';
        auto queue = device->get_queue();

        int counter = 0;

        toPrint += "   ";

        while(!queue.empty()){
            toPrint += display(queue.front()) + " ";
            queue.pop();
            counter++;

            if(counter == 1){
                toPrint += " | ";
                counter++;
            }
        }

        toPrint += '\n';
    }
    toPrint += '\n';
    return toPrint;
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
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling systemStart");
    REQUIRE(documentStarted(), "Document was not started when calling systemStart");
    onStream << "# === [" << title << "] === #" << std::endl;
}

void SystemExporter::devicesStart (std::ostream& onStream) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling devicesStart");
    REQUIRE(documentStarted(), "Document was not started when calling devicesStart");
    onStream << "--== Devices ==--" << std::endl;
}

void SystemExporter::deviceName(ostream &onStream, Device *device) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling deviceName");
    REQUIRE(documentStarted(), "Document was not started when calling deviceName");
    onStream << device->getName() << ":" << std::endl;
}

void SystemExporter::deviceEmissions(ostream &onStream, Device *device) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling deviceEmissions");
    REQUIRE(documentStarted(), "Document was not started when calling deviceEmissions");
    onStream << "* " << device->getEmissions() << "g/page" << std::endl;
}

void SystemExporter::deviceSpeed(ostream &onStream, Device *device) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling deviceSpeed");
    REQUIRE(documentStarted(), "Document was not started when calling deviceSpeed");
    onStream << "* " << device->getSpeed() << " pages / minute" << std::endl;
}

void SystemExporter::deviceType(ostream &onStream, Device *device) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling deviceType");
    REQUIRE(documentStarted(), "Document was not started when calling deviceType");
    onStream << "* " << device->getType() << std::endl;
}

void SystemExporter::deviceCosts(ostream &onStream, Device *device) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling deviceCosts");
    REQUIRE(documentStarted(), "Document was not started when calling deviceCosts");
    onStream << "* " << device->getCosts() << " cents / page"<< std::endl;
}

void SystemExporter::jobsStart (std::ostream& onStream) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobsStart");
    REQUIRE(documentStarted(), "Document was not started when calling jobsStart");
    onStream << "--== Jobs ==--" << std::endl;
}

void SystemExporter::jobNumber(ostream &onStream, Job *job) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobNumber");
    REQUIRE(documentStarted(), "Document was not started when calling jobNumber");
    onStream << "[Job #" << job->getJobNumber() << "]" << std::endl;
}

void SystemExporter::jobOwner(ostream &onStream, Job *job) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobOwner");
    REQUIRE(documentStarted(), "Document was not started when calling jobOwner");
    onStream << "* Owner: " << job->getOwner() << std::endl;
}

void SystemExporter::jobDevice(ostream &onStream, Job *job) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobDevice");
    REQUIRE(documentStarted(), "Document was not started when calling jobDevice");
    onStream << "* Device: " << job->getDevice() << std::endl;
}

void SystemExporter::jobStatus(ostream &onStream, Job *job) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobStatus");
    REQUIRE(documentStarted(), "Document was not started when calling jobStatus");
    onStream << "* Status: " << job->getStatus() << std::endl;
}

void SystemExporter::jobTotalPages(ostream &onStream, Job *job) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobTotalPages");
    REQUIRE(documentStarted(), "Document was not started when calling jobTotalPages");
    onStream << "* Total pages: " << job->getTotalPages() << " pages" << std::endl;
}

void SystemExporter::jobTotalCO2(ostream &onStream, Job *job) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobTotalCO2");
    REQUIRE(documentStarted(), "Document was not started when calling jobTotalCO2");
    onStream << "* Total CO2: " << job->getTotalCO2() << "g CO2"<< std::endl;
}

void SystemExporter::jobTotalCost(ostream &onStream, Job *job) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling jobTotalCost");
    REQUIRE(documentStarted(), "Document was not started when calling jobTotalCost");
    onStream << "* Total cost: " << job->getTotalCost() << " cents" << std::endl;
}

void SystemExporter::compensationStart (std::ostream& onStream) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling compensationStart");
    REQUIRE(documentStarted(), "Document was not started when calling compensationStart");
    onStream << "--== Co2 Compensation initiatives ==--" << std::endl;
}

void SystemExporter::whitespace(ostream &onStream) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling whitespace");
    REQUIRE(documentStarted(), "Document was not started when calling whitespace");
    onStream << endl;
}

void SystemExporter::systemEnd (std::ostream& onStream) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling systemEnd");
    REQUIRE(documentStarted(), "Document was not started when calling systemEnd");
    onStream << "# ======================= #" << std::endl;
}

void SystemExporter::output(ostream &onStream, System &system) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling output");
    REQUIRE(documentStarted(), "Document was not started when calling output");
}

void SimpleExporter::output(ostream &onStream, System &system) {
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

void AdvancedTextualExporter::output(ostream &onStream, System &system) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling advanced_textual_output");
    REQUIRE(documentStarted(), "Document was not started when calling advanced_textual_output");

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

void StatisticsExporter::output(ostream &onStream, System &system) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling statistics_output");
    REQUIRE(documentStarted(), "Document was not started when calling statistics_output");

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

void GraphicsExporter::output(ostream &onStream, System &system) {
    REQUIRE(properlyInitialized(), "SystemExporter wasn't initialized when calling graphics_output");
    REQUIRE(documentStarted(), "Document was not started when calling graphics_output");

    onStream << "[General]" << endl;
    onStream << "type = \"Wireframe\"" << endl;
    onStream << "size = 1000" << endl;
    onStream << "backgroundcolor = (0, 0, 0)" << endl;

    int unfinished_jobs = 0;

    for (auto job : system.getJobs()) {
        if(!job->getFinished()){
            unfinished_jobs++;
        }
    }

    onStream << "nrFigures = " << system.getDevices().size() + unfinished_jobs << endl;
    onStream << "eye = (100, 50, 75)" << endl << endl;

    int figure_counter = 0;
    for (long long unsigned int i = 0; i < system.getDevices().size(); ++i) {
        onStream << "[Figure" << figure_counter << "]" << endl;
        onStream << "type = \"Cube\"" << endl;

        if(system.getDevices()[i]->get_queue().empty()){
            // GREEN = FREE
            onStream << "color = (0, 1, 0)" << endl;
        }
        else {
            // RED = BUSY
            onStream << "color = (1, 0, 0)" << endl;
        }

        onStream << "scale = 1" << endl;
        onStream << "rotateX = 0" << endl;
        onStream << "rotateY = 0" << endl;
        onStream << "rotateZ = 0" << endl;
        onStream << "center = (0, " << i*4 << ", 0)" << endl;

        onStream << endl;

        if(!system.getDevices()[i]->get_queue().empty()) {
            for (long long unsigned int job = 0; job < system.getDevices()[i]->get_queue().size(); ++job) {
                figure_counter++;
                onStream << "[Figure" << figure_counter << "]" << endl;
                onStream << "type = \"Cube\"" << endl;
                onStream << "color = (0, 0, 1)" << endl;
                onStream << "scale = 0.2" << endl;
                onStream << "rotateX = 0" << endl;
                onStream << "rotateY = 0" << endl;
                onStream << "rotateZ = 0" << endl;
                onStream << "center = (0, " << i * 4 << ", " << -1 + job * 0.4 << ")" << endl;

                onStream << endl;
            }
        }

        figure_counter++;
    }

    graphics();
}
