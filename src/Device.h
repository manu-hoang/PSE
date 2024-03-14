#pragma once

#include <vector>
#include "string"
#include "Job.h"

using namespace std;

/*
    Device type                 CO2 limit
    Black-and-white printers    8g CO2 per page
    Color printers              23g CO2 per page
    Scanner                     12g CO2 per page
 */

class Device {
private:
    string name;
    int emissions; // gram CO2 per page
    double speed; // pages per minute

    bool busy;

    Job* current_job;
    vector<Job*> jobs;
    double printing_time; // time to complete current job (seconds)

public:
    Device(string name, int emissions, double speed): name(name), emissions(emissions), speed(speed){
        busy = false;
        current_job = nullptr;
    }

    void print_page();

    void update_current_job(int current_time);





    void add_job(Job *&job);
    Job* getCurrentJob();

    double get_printing_time();

    //Functions used for PrinterOutput.cpp
    const string &getName() const;
    int getEmissions() const;
    string getQueueInfo();
    string getCurrentInfo();

    void setBusy(bool busy);
    bool getBusy();
    //
};

